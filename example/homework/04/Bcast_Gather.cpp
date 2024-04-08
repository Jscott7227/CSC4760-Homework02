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

    //Create a buffer to hold values and create a float to store individual values
    float recvbuf[5];
    float sendval;

    sendval = (float)rank;

    //Gather all values to the root rank, rank 0
    MPI_Gather(&sendval, 1, MPI_FLOAT, recvbuf, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    //Send the values gathered by the root to all other nodes
    MPI_Bcast(recvbuf, 5, MPI_FLOAT, 0, MPI_COMM_WORLD);

    //These two call are functionaly the same as MPI_AllGather

    //Print the values for each rank should be the same for each rank
    cout << rank << ": ";
    
    for(int i = 0; i < size; ++i)
        cout << recvbuf[i] << ", ";
    
    cout << endl;
    
    MPI_Finalize();

    

    return 0;
}
