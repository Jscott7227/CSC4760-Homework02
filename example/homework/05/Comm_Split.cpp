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

    int color1, color2;
    //Assign P and Q assume size is a multiple of P
    int P = 2;
    int Q = size/ P;
    
    //First split should be split into groups either 1 or 0 
    color1 = rank / Q;

    MPI_Comm comm1;
    MPI_Comm_split(MPI_COMM_WORLD, color1, rank, &comm1);

  
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //Second Split splits the processes into size / 2 different sections
    color2 = rank % Q;

    MPI_Comm comm2;
    MPI_Comm_split(MPI_COMM_WORLD, color2, rank, &comm2);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    cout << "Rank: " << rank << " Group: " << color1 << " Section: "<< color2 << endl;

    MPI_Finalize();
    return 0;
 
}
