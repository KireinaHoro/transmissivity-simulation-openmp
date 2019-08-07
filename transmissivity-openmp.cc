#include <cstdint>
#include <iostream>
#include <random>
#include <stdexcept>

#include "common.h"

/*!
 * \brief Simulate the scatter rate of neutrons across some material in a
 * parallel manner with OpenMP.
 * \param a depth of the matter.
 * \param b mean free path.
 * \param p rate of absorption.
 * \param n number of particles.
 * \return transmissivity.
 */
double simulate_transmissivity_openmp(double a, double b, double p, uint64_t n,
                                      std::mt19937 engine) {
  static RandomDouble gen(engine);
#pragma omp threadprivate(gen)
  uint64_t count = 0;
#pragma omp parallel for reduction(+ : count) schedule(dynamic, 4)
  for (uint64_t i = 0; i < n; ++i) {
    double x = 0;
    double cc = 1;
    while (x >= 0 && x <= a) {
      double lg_xi = log(gen.next_double(0, 1));
      double ccl = gen.next_double(-1, 1);
      double phi = gen.next_double(0, 2 * M_PIl);
      double zeta = gen.next_double(0, 1);
      x -= b * cc * lg_xi;
      cc = cc * ccl + cos_to_sin(cc) * cos_to_sin(ccl) * cos(phi);
      if (zeta < p) {
        count += 1;
        break;
      }
    }
  }
  std::cout << "count = " << count << std::endl;
  return (double)(n - count) / n;
}
