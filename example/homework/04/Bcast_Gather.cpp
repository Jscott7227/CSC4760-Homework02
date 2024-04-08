#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    float recvbuf[5];
    float sendval;

    sendval = (float)rank;

    MPI_Gather(&sendval, 1, MPI_FLOAT, recvbuf, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(recvbuf, 5, MPI_FLOAT, 0, MPI_COMM_WORLD);

    cout << rank << ": ";
    
    for(int i = 0; i < 5; ++i)
        cout << recvbuf[i] << ", ";
    
    cout << endl;
    MPI_Finalize();

    

    return 0;
}
