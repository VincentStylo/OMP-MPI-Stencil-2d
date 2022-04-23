

// Include Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Main Program
int main(int argc, char *argv[])
{

    
    //Creation of Variables
    FILE *fp;
    char rows_A[10], columns_A[10];
    int row, column;


    // Checks to see if arguments are satisfied
    if (argc != 4)
    {
        printf("usage: ./make-2d <rows> <columns> <output file> \n");
        exit(0);
    }


    // Takes input <rows> <columns> and converts them from string to int
    strcpy(rows_A, argv[1]);
    strcpy(columns_A, argv[2]);
    row = atoi(rows_A);
    column = atoi(columns_A);
    double one = 1;
    double zero = 0;


    // Creates <output file> , and putting a stencil with the dimensions of <rows> <columns>
    fp = fopen(argv[3], "w");
    fwrite(&row, 1, sizeof(int), fp);
    fwrite(&column, 1, sizeof(int), fp);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (j == 0  || j == column-1)
            {
                fwrite(&one, 1, sizeof(double), fp);
            } else {
                fwrite(&zero, 1, sizeof(double), fp);
	    } 
        }
        
    }
    fclose(fp);
    return 0;
}
