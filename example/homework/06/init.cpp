#include <Kokkos_Core.hpp>
#include <mpi.h>
#include <cstdio>
#include <iostream>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    Kokkos::initialize(argc, argv);
    {
      int rank, size;
      MPI_Comm_rank(MPI_COMM_WORLD, &rank);
      MPI_Comm_size(MPI_COMM_WORLD, &size);
	
      // Make View and init values
      int N = 20;
      Kokkos::View<int*> A("A", N);

      if (0 == rank)
      {
        Kokkos::parallel_for("Loop1", A.extent(0), KOKKOS_LAMBDA (const int i) {
        //Asign value to A
		    A(i) = (i*3)+(i*4);
        });

        // Send View values with MPI functions
        MPI_Send(A.data(), A.size(), MPI_INT, 1, 0, MPI_COMM_WORLD);

      }

      if (1 == rank)
      { 
        // Recive View
        MPI_Recv(A.data(), A.size(), MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Output
        for (int i = 0; i < A.size(); i++)
        {
          std::cout << A[i] << ", ";
        }

	std::cout << std::endl;

      }
    }
    Kokkos::finalize();
    MPI_Finalize();
}
