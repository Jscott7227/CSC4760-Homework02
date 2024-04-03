#include <Kokkos_Core.hpp>
#include <cstdio>

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // Make View of length n > 1000 and add values
  int N = 2000;
  Kokkos::View<int*> A("Original", N);
  
  Kokkos::parallel_for("Loop1", A.extent(0), KOKKOS_LAMBDA (const int i) {
      //Asign value to A
		  A(i) = (i+3)*i;
    });

  // create two additional views of same size and datatype
  Kokkos::View<int*> B("Deep_copy", N);
  Kokkos::View<int*> C("User_copy", N);


  Kokkos::Timer timer;
  // deep_copy
  Kokkos::deep_copy(B, A);
  
  double deep_time = timer.seconds();

  timer.reset();
  // user copy

  Kokkos::parallel_for("Loop1", B.extent(0), KOKKOS_LAMBDA (const int i) {
		  C(i) = A(i);
    });

  double user_time = timer.seconds();
  // Output times 

  std::cout << "Time for deep copy:" << deep_time << std::endl;
  std::cout << "Time for user copy:" << user_time << std::endl;

  }
  Kokkos::finalize();
}
