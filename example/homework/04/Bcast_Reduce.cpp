#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    int rank, size;
    
    //Get rank information
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Create a buffer to hold the send values and a float to hold the recived value. 
    float sendbuf[5], recvbuf;


    for(int i = 0; i < 5; ++i)
       sendbuf[i] = (float)rank;

    //Use reduce to take all elements from other ranks and convert them into a single value on the root rank 0
    MPI_Reduce(&sendbuf, &recvbuf, 5, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    //Send the value in recvbuf on the root rank to all other ranks
    MPI_Bcast(&recvbuf, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    //Print value of recvbuf for all ranks
    cout << rank << ": ";
    
    cout << recvbuf << ", ";
    
    cout << endl;
    MPI_Finalize();

    

    return 0;
}
