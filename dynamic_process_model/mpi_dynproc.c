#include <stdio.h> 
//#include <stdlib.h> 
// #include <string.h> 
#include "mpi.h"
int main(int argc, char **argv) 
{
  char message[20];
  int  i, rank, size, tag = 99;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    strcpy(message, "Hello, world");
    for (i = 1; i < size; i++) 
      MPI_Send(message, 13, MPI_CHAR, i, tag, MPI_COMM_WORLD);
  }
  else {
    MPI_Recv(message, 20, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
  }

  printf( "Message from process %d : %.13s\n", rank, message);

  // Just hello_mpi until now. 
  // Now we can try dynamic process creation.
  
  int max_procs = 3;
  MPI_Info info;
  int root = 0;
  int errors[max_procs]; // should it be max_proces*size?

  MPI_Comm_spawn("./hello_mpi", argv, max_procs,
		 info, root, MPI_COMM_WORLD, MPI_Comm *intercomm,
		 errors)

  MPI_Finalize();
}

