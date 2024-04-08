#include "mpi.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv)
{
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    //Create the recv buf and the send buf
    //Zero out the recv buff and assign values to the sendbuf per rank
    int sendbuf[3];
    int recvbuf[3];

    for(int i = 0; i < 3; i++)
	recvbuf[i] = 0;

    for(int i = 0; i < 3; i++)
    {
        sendbuf[i] = rank * 10 + i * 10;
    
    }
    
    // Sendbuf[i] should be sent to rank i
    // So sendbuf[0] for all ranks is sent to rank 0
    // Henceforth recvbuf[i] was recived from rank i
    // So recvbuf[0] for all ranks was sent from rank 0
	
     printf("Process %d, my values = %d, %d, %d.\n", rank, sendbuf[0], sendbuf[1], sendbuf[2]);
	
    MPI_Alltoall(&sendbuf, 1, MPI_INT, recvbuf, 1, MPI_INT, MPI_COMM_WORLD);

    for(int i = 0; i < 3; i++)
    {
	cout << rank << " Recived " << recvbuf[i] << " from rank " << i << endl; 
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}
