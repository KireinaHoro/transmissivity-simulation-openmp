#include <iostream>
#include <random>

#include "omp.h"

#include "common.h"

int omp_thread_count() {
  int n = 0;
#pragma omp parallel reduction(+ : n)
  n += 1;
  return n;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "usage: " << argv[0] << " <lg_n>" << std::endl;
    return EXIT_FAILURE;
  }
  const double a = 50, b = 2.6, p = 8e-5;
  uint64_t n = pow(10, atoi(argv[1]));

  std::random_device rd;
  std::mt19937 gen(rd());
  double serial_t, openmp_t;
  std::cout << "Starting OpenMP impl. with " << omp_thread_count()
            << " threads..." << std::endl;
  TIME_AND_REPORT("OpenMP",
                  openmp_t = simulate_transmissivity_openmp(a, b, p, n, gen))
  std::cout << "OpenMP result: " << openmp_t << std::endl;

  std::cout << "Starting serial impl. ..." << std::endl;
  TIME_AND_REPORT("Serial",
                  serial_t = simulate_transmissivity_serial(a, b, p, n, gen))
  std::cout << "Serial result: " << serial_t << std::endl;

  return EXIT_SUCCESS;
}
