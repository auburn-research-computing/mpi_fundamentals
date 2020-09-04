//
//  mpi_send.cpp
//  A simple MPI program

// include the MPI header file so that we can use
// the provided functions ...

#include <stdio.h>
#include <mpi.h>

int main(int argc, const char * argv[]) {

	// initialize MPI environment ...
    
	int world_rank; // used to track MPI rank
	int world_size; // tracks the communicator size
	
	MPI_Init(NULL, NULL);
    
	// find the size of the mpi communicator ...

	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// find the rank of *this* running process ...
   
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	// print the rank of *this* running process ...

	printf("hello from rank %d\n", world_rank);

	int number = 8;

	if(world_rank == 0) {
        	MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("SENDING (RANK %d) number %d to rank %d\n", world_rank, number, 1);
	} else if(world_rank == 1) {
        	MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("RECEIVED (RANK %d) number %d from rank %d\n", world_rank, number, 0);
	} else {
		printf("NOTHING (RANK %d) didn't receive anything :(\n", world_rank);
	}
	MPI_Finalize();

}
