#ifndef COMMON_H_
#define COMMON_H_

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <ctime>

#define TIME_AND_REPORT(NAME, ...)                                             \
  {                                                                            \
    struct timespec start, end;                                                \
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);                                \
    __VA_ARGS__;                                                               \
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);                                  \
    uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 +                \
                        (end.tv_nsec - start.tv_nsec) / 1000;                  \
    double delta_ms = (double)delta_us / 1000.0;                               \
    printf("TIMER: %-40s took %.3lfms.\n", NAME, delta_ms);                    \
  }

inline double cos_to_sin(double c) {
  double c2 = c * c;
  return sqrt(1 - c2);
}

struct RandomDouble {
  std::mt19937 rng;
  std::uniform_real_distribution<double> urd;

  RandomDouble(std::mt19937 &engine) : rng(engine) {}

  double next_double(double low, double high) {
    return urd(rng, decltype(urd)::param_type(low, high));
  }
};

double simulate_transmissivity_serial(double a, double b, double p, uint64_t n,
                                      std::mt19937 gen);
double simulate_transmissivity_openmp(double a, double b, double p, uint64_t n,
                                      std::mt19937 gen);

#endif // COMMON_H_
