//
//  mpi_bcast.cpp
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

	// initialize a number to 0 for all processes ...

	int number = 0;

	// set the number to 8 for only process 0 ...

	if(world_rank == 0) {
		number = 8;
	}

	// send a broadcast of process 0's number to all processes ...

	MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// now, what is our number value after the broadcast? ...

	printf("Process %d received %d from process 0\n", world_rank, number);
	
	MPI_Finalize();

}
