// Included Libraries
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <mpi.h>
#include "utilities.h"
#include "MyMPI.h"
#define dtype double

// This Memory Allocation was created by Bob Robey
double **malloc2D(int jmax, int imax)
{
   // Allocate a block of memory for the row pointers and the 2D array
   double **x = (double **)malloc(jmax*sizeof(double *) + jmax*imax*sizeof(double));

   // Now assign the start of the block of memory for the 2D array after the row pointers
   x[0] = (double *)(x + jmax);

   // Last, assign the memory location to point to for each row pointer
   for (int j = 1; j < jmax; j++) {
      x[j] = x[j-1] + imax;
   }

   return(x);
}

// Function does the Stencil Operation with OpenMP
double **calc2D_Parallel(double **x, double **xnew, int row, int column)
{
   #pragma omp parallel for 
   for (int a = 1; a < row - 1; a++){
      for (int b = 1; b < column -1; b++){
         xnew[a][b] = (x[a - 1][b - 1] + x[a - 1][b] + x[a - 1][b + 1] + x[a][b + 1] + x[a + 1][b + 1] + x[a + 1][b] + x[a + 1][b - 1] + x[a][b - 1] + x[a][b]) / 9.0;
      }
   }
   return (xnew);
}

// Function does the Stencil Operation with OpenMPI
double **calc2D_MPI(double **x, double **xnew, int row, int column)
{
   
   int id;             /* Process rank */
   int p;              /* Number of processes */
   int local_rows;     /* This proc's rows */
   int temp_m = 0;
   int start = 1;
   MPI_Comm_rank(MPI_COMM_WORLD, &id);
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   local_rows = BLOCK_SIZE(id, p, row);
   if (id == 0 || id == p - 1){ temp_m = 1;} else{temp_m = 2;}
   for (int a = start; a < (local_rows + temp_m) - 1; a++){
      for (int b = 1; b < (column -1); b++){
         xnew[a][b] = (x[a - 1][b - 1] + x[a - 1][b] + x[a - 1][b + 1] + x[a][b + 1] + x[a + 1][b + 1] + x[a + 1][b] + x[a + 1][b - 1] + x[a][b - 1] + x[a][b]) / 9.0;
      }
   }
   return (xnew);
}

// Function does the Stencil Operation with no parallelization
double **calc2D_Serial(double **x, double **xnew, int row, int column)
{
   for (int a = 1; a < row - 1; a++){
      for (int b = 1; b < column -1; b++){
         xnew[a][b] = (x[a - 1][b - 1] + x[a - 1][b] + x[a - 1][b + 1] + x[a][b + 1] + x[a + 1][b + 1] + x[a + 1][b] + x[a + 1][b - 1] + x[a][b - 1] + x[a][b]) / 9.0;
      }
   }
   return (xnew);
}