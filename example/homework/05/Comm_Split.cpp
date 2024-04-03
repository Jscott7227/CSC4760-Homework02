#include "mpi.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv)
{
    cout << "MPI allreduce";
    int rank0, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank0);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //First split not right fix later
    char subcommunicator;
    int color;
    int key;
    int Q = 2;

    color = rank0 % Q;
    key = rank0;

    MPI_Comm comm1;
    MPI_Comm_split(MPI_COMM_WORLD, color, key, &comm1);

    int rank1;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank1);

    //Second Split should be correct
    color = rank1 % Q;
    key = rank1;

    MPI_Comm comm2;
    MPI_Comm_split(MPI_COMM_WORLD, color, key, &comm2);

    int rank2;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank2);

    printf("Oringinal Rank: %d \nFirst split Rank: %d \nSecond split Rank: %d", rank0, rank1, rank2);

    MPI_Finalize();
    return 0;
}