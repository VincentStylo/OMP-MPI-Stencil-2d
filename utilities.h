#ifndef _UTILITIES_H
#define _UTILITIES_H
double **malloc2D(int jmax, int imax);
double** calc2D_Parallel(double **x, double **xnew, int row, int column);
double** calc2D_MPI(double **x, double **xnew, int row, int column);
double** calc2D_Serial(double **x, double **xnew, int row, int column);
#endif