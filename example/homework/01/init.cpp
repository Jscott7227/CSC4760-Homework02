#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    int rank, size;
    int N_loops = 10;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int myvalue = 0;
    MPI_Send(&myvalue, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    cout << "Sending: " << myvalue << endl;

    for (int i = 0; i < N_loops; i++)
    {

        int myvalue = 0;
        MPI_Recv(&myvalue, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Received: " << myvalue << endl;
        myvalue++;
        MPI_Send(&myvalue, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        cout << "Sending: " << myvalue << endl;

    }
    MPI_Finalize();

   return 0;
}