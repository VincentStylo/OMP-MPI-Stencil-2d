/* 
 * Code by Jose Martinez Torres
 * This is mpi-stencil-2d
 * Outputs to screen the elapsed time in seconds, number-
 * of iterations, along with row and column 
 * 
 */

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>
#include <omp.h>
#include "MyMPI.h"
#include "utilities.h"
#include "timer.h"
#define dtype double

#define SWAP_PTR(xnew,xold,xtmp) (xtmp=xnew, xnew=xold, xold=xtmp)

// main program
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int id;             /* Process rank */
    int p;              /* Number of processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    // Checks to see if arguments are satisfied
    if (argc != 4)
    {
        printf("usage: ./mpi-stencil-2d <num iterations> <input file> <output file> \n");
        MPI_Finalize();
        exit(1);
    }

    //Row, Column, Iteration, and Timer are created
    int row = 0, column = 0, iteration = 0;
    char iteration_A[10];
    strcpy(iteration_A, argv[1]);
    iteration = atoi(iteration_A);
    double Start = 0, End, Elapsed;
    
    // Quinn Memory Allocation
    dtype **xtmp;
    dtype **x, *xData;
    dtype **xnew, *xnewData;

    if (id == 0)
    {
        printf("Reading from file: %s \n", argv[2]);
    }
    
    

    // Loads values from <input file>
    read_row_striped_matrix_halo(argv[2], (void ***)&x, (void **)&xData, MPI_DOUBLE, &row, &column, MPI_COMM_WORLD);
    read_row_striped_matrix_halo(argv[2], (void ***)&xnew, (void **)&xnewData, MPI_DOUBLE, &row, &column, MPI_COMM_WORLD);

    exchange_row_striped_matix_halo((void **)x, MPI_DOUBLE, row, column, MPI_COMM_WORLD);
    exchange_row_striped_matix_halo((void **)xnew, MPI_DOUBLE, row, column, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    if (id == 0)
    {
        GET_TIME(Start);
    }

    // Does Stencil Operation 
    for (int i = 0; i < iteration; i++)
    {
        calc2D_MPI(x, xnew, row, column);
        exchange_row_striped_matix_halo((void **)xnew, MPI_DOUBLE, row, column, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        SWAP_PTR(xnew, x, xtmp);
    }

    if (id == 0)
    {
        printf("Writing to:%s \n", argv[3]);
    }

    write_row_striped_matrix_halo(argv[3], (void**)x, MPI_DOUBLE, row, column, MPI_COMM_WORLD);
    
    // Frees X, stops the timer, and Ends Program
    free(x);
    free(xnew);
    if (id == 0)
    {
        GET_TIME(End);
        Elapsed = End - Start;
        printf("Elapsed time =  %f \nNumber of iterations = %d \nRows: %d, Columns: %d\n", Elapsed, iteration, row, column);
    }
    MPI_Finalize();
    return 0;
}
