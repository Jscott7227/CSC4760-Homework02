#include "mpi.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv)
{
    cout << "MPI allreduce";
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int sendbuf[3];
    int recvbuf[3];


    switch(rank)
    {
        case 0:
            sendbuf[0] = 10;
            sendbuf[1] = 20;
            sendbuf[2] = 30;
            printf("Process %d, my values = %d, %d, %d.\n", rank, sendbuf[0], sendbuf[1], sendbuf[2]);
            break;
        case 1:
            sendbuf[0] = 11;
            sendbuf[1] = 21;
            sendbuf[2] = 31;
            printf("Process %d, my values = %d, %d, %d.\n", rank, sendbuf[0], sendbuf[1], sendbuf[2]);
            break;
        case 2:
            sendbuf[0] = 12;
            sendbuf[1] = 22;
            sendbuf[2] = 32;
            printf("Process %d, my value = %d, %d, %d.\n", rank, sendbuf[0], sendbuf[1], sendbuf[2]);
            break;
    }

    MPI_Alltoall(sendbuf, 3, MPI_INT, recvbuf, 3, MPI_INT, MPI_COMM_WORLD);

    cout << "Values received on process " << rank;
    for(int i = 0; i < 3; i++)
    {
        cout << recvbuf[i] << " from rank " << i << endl; 
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}