//Code by Jose Martinez Torres


// Included Libraries
#include <stdio.h>
#include <stdlib.h>


// Main Program
int main(int argc, char *argv[])
{
   // Creates File Pointer, Row, Column, and temp
   FILE * fp;
   int row = 0;
   int column = 0;
   double temp = 0;


   //Checks to see if arguments are satisfied
   if (argc < 2 || argc > 2)
   {
      printf("usage: ./print-2d <input data file> \n");
      exit(0);
   }


   //opens <input data file>, takes first two ints to create for loop
   fp = fopen(argv[1], "r");
   fread(&row, sizeof(int), 1, fp);
   fread(&column, sizeof(int), 1, fp);
   printf("reading in file: ./%s \n", argv[1]);


   //Prints out <input data file> stencil
   for (int i = 0; i < row; i++)
   {
      for (int j = 0; j < column; j++){
         fread(&temp, sizeof(double),1, fp);
         printf("%.2f ", temp);
      }
      printf("\n");
   }


fclose(fp);
return 0;
}
