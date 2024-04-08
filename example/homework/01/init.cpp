#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int value = 0;
    const int num_iterations = 5; // Number of times the message will go around the ring

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = 0; i < num_iterations; ++i) {
	// Create ring of processes inside for loop
	// Iterating [num_iterations] times or 5 times in this case
        if (rank == 0) {
            MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process %d received value: %d\n", rank, value);
        } else {
            MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process %d received value: %d\n", rank, value);
            MPI_Send(&value, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
        }
	//Increment value at the end of the for loop for a counter
	value++;
    }

    MPI_Finalize();
    return 0;
}
