//
//  main.cpp
//  Created by Bradley Morgan on 09.01.20
//
//  hello_mpi.cpp
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

	MPI_Finalize();

}
