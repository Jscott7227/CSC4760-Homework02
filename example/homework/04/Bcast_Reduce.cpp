#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    cout << "MPI allreduce";
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    float sendbuf[5], recvbuf[5];

    for(int i = 0; i < 5; ++i)
       sendbuf[i] = (float)rank;

    MPI_Reduce(sendbuf, recvbuf, 5, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Bcast(recvbuf, 5, MPI_FLOAT, 0, MPI_COMM_WORLD);

    cout << rank << ": ";
    
    for(int i = 0; i < 5; ++i)
        cout << recvbuf[i] << ", ";
    
    cout << endl;
    MPI_Finalize();

    

    return 0;
}