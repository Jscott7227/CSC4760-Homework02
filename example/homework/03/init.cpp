#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>

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


  Kokkos::Timer timer; // Time for deep copy starts here
  // deep_copy
  Kokkos::deep_copy(B, A);
  
  double deep_time = timer.seconds(); // Record time for deep copy

  timer.reset(); // Time for user copy
  // user copy

  Kokkos::parallel_for("Loop1", B.extent(0), KOKKOS_LAMBDA (const int i) {
		  C(i) = A(i);
    });

  double user_time = timer.seconds(); // Record time for user copy
  // Output times 
  
  std::cout << "B(5): " << B(5) << ", A(5) " << A(5) << std::endl;
  std::cout << "C(5): " << C(5) << ", A(5) " << A(5) << std::endl;  
  std::cout << "Time for deep copy:" << deep_time << std::endl;
  std::cout << "Time for user copy:" << user_time << std::endl;

  // Fairly similar times between each with the kokkos deep copy being
  // slightly faster than the user made copy.
  // This implies that the deep copy is similar to the user copy just more
  // optimized.

  }
  Kokkos::finalize();
}
