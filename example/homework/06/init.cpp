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
		    A(i) = (i+3)*i;
        });

        // Send View values with MPI functions
        MPI_Send(A.data(), A.size(), MPI_INT, 1, 0, MPI_COMM_WORLD);

      }

      else
      {
        // Recive View
        MPI_Recv(A.data(), A.size(), MPI_INT, 1, 0, MPI_COMM_WORLD);

        // Output
        for (int i = 0; i < A.size(); i++)
        {
          std::cout << A[i] << ", ";
        }

      }


    printf("\nhello world\n");
    }
    Kokkos::finalize();
    MPI_Finalize();
}
