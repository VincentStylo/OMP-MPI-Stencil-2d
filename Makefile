CFLAGS=-g -Wall -Wstrict-prototypes -std=gnu99
LFLAGS=-lm 
OMP=-fopenmp
CC=gcc
MCC=mpicc
PROGS = print-2d make-2d stencil-2d stencil-2d-stack omp-stencil-2d omp-stencil-2d-stack mpi-stencil-2d mpi-stencil-2d-stack
all: $(PROGS)
driver: utilities.o driver.o timer.o MyMPI.o
	$(CC) $(MCC) $(LFLAGS) -o driver utilities.o driver.o timer.o MyMPI.o
print-2d:	utilities.o print-2d.o
	$(CC) $(LFLAGS) -o print-2d print-2d.o
make-2d:	utilities.o make-2d.o
	$(CC) $(LFLAGS) -o make-2d make-2d.o
stencil-2d:	utilities.o stencil-2d.o
	$(MCC) $(OMP) $(LFLAGS) -o stencil-2d utilities.o stencil-2d.o
stencil-2d-stack: utilities.o stencil-2d-stack.o
	$(MCC) $(OMP) $(LFLAGS) -o stencil-2d-stack utilities.o stencil-2d-stack.o
omp-stencil-2d: utilities.o omp-stencil-2d.o
	$(MCC) $(LFLAGS) $(OMP) -o omp-stencil-2d utilities.o omp-stencil-2d.o
omp-stencil-2d-stack: utilities.o omp-stencil-2d-stack.o
	$(MCC) $(LFLAGS) $(OMP) -o omp-stencil-2d-stack utilities.o omp-stencil-2d-stack.o
mpi-stencil-2d: utilities.o MyMPI.o mpi-stencil-2d.o
	$(MCC) $(OMP) $(CFLAGS) -o mpi-stencil-2d utilities.o MyMPI.o mpi-stencil-2d.o
mpi-stencil-2d-stack: utilities.o MyMPI.o mpi-stencil-2d-stack.o
	$(MCC) $(OMP) $(CFLAGS) -o mpi-stencil-2d-stack utilities.o MyMPI.o mpi-stencil-2d-stack.o
utilities.o: utilities.c utilities.h MyMPI.h
	$(MCC) $(OMP) $(LFLAGS) -c utilities.c 
driver.o: driver.c utilities.h
	$(CC) $(LFLAGS) -c driver.c
print-2d.o: print-2d.c utilities.h
	$(CC) $(LFLAGS) -c print-2d.c
make-2d.o: make-2d.c utilities.h
	$(CC) $(LFLAGS) -c make-2d.c
stencil-2d.o: stencil-2d.c utilities.h
	$(CC) $(LFLAGS) -c stencil-2d.c
stencil-2d-stack.o: stencil-2d-stack.c utilities.h
	$(CC) $(LFLAGS) -c stencil-2d-stack.c
omp-stencil-2d.o: omp-stencil-2d.c utilities.h
	$(CC) $(LFLAGS) $(OMP) -c omp-stencil-2d.c
omp-stencil-2d-stack.o: omp-stencil-2d-stack.c utilities.h
	$(CC) $(LFLAGS) $(OMP) -c omp-stencil-2d-stack.c
mpi-stencil-2d.o: mpi-stencil-2d.c utilities.h MyMPI.h
	$(MCC) $(CFLAGS) -c mpi-stencil-2d.c
mpi-stencil-2d-stack.o: mpi-stencil-2d-stack.c utilities.h MyMPI.h
	$(MCC) $(CFLAGS) -c mpi-stencil-2d-stack.c	
MyMPI.o: MyMPI.h MyMPI.c
	$(MCC) $(CFLAGS) -c MyMPI.c
clean:
	rm -f $(PROGS) *.o *.exe core* 
clean-windows:
	del -f $(PROGS) *.o *.exe core*

