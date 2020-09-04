//
//  mpi_scatter.cpp
//  A simple MPI program

// include the MPI header file so that we can use
// the provided functions ...

#include <cstdlib>
#include <stdio.h>
#include <mpi.h>

const int chunk_size = 5;

int main(int argc, const char * argv[]) {

	// initialize MPI environment ...
	
	int world_rank; // used to track MPI rank
	int world_size; // tracks the communicator size

	MPI_Init(NULL, NULL);
    
	// find the size of the mpi communicator ...

	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// find the rank of *this* running process ...
   
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
	// create two arrays of int, one to hold our full data set,
	// and one to hold a subset of data ...	

	int data[world_size*chunk_size];
	int subdata[chunk_size];

	// only rank 0 will have to deal with the full data set ...

	if(world_rank == 0) {
                for(int i=0; i<(world_size*chunk_size); i++) {
                        data[i] = i;
                }
		printf("\nScattering %lu integers to %d processes holding %lu each\n\n", sizeof(data)/sizeof(int), world_size, sizeof(subdata)/sizeof(int));
	}

	// now, distribute the data evenly among all processes ...

	MPI_Scatter(data, chunk_size, MPI_INT, subdata, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

	// now that each process has received its chunk of data, 
	// each can do its part ...

	int total = 0;

	// calculate the sum of *this* processes data ...

	for(int i=0; i<chunk_size; i++) {
		total += subdata[i];
	}	
	
	// calculate the average of *this* processes data ...

	float avg = total / chunk_size;

	// print some output to tell everyone what we have ...	
	
	printf("Process %d ", world_rank);
	for(int i=0; i<chunk_size; i++) {
		printf("subdata[%d] = %2d | ", i, subdata[i]);
	}
	printf("average = %f\n", avg);

	float avgs[world_size];

	// now, let's send our findings back to the root process ...

	MPI_Gather(&avg, 1, MPI_FLOAT, avgs, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

	// and now the root process can calculate the full average based on
	// what all processes have found ...
	
	if(world_rank == 0) {
		float sum = 0.0;
		for(int i=0; i < world_size; i++) {
			sum += avgs[i];
		}
		float world_avg = sum / world_size;
		printf("\n *** World average = %f *** \n\n\n", world_avg);
	}	
		
	MPI_Finalize();

}
