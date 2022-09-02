/*
 * FILE: main.cpp
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <iostream>
#include <chrono>

#include <numeric>
#include <execution>

#include "implementations.h"

int main()
{
  int nrep = 10000000;
  int n = 10000000;

  std::vector<double> x;
  std::vector<double> y;

  x.reserve(n);
  y.reserve(n);
  for (int i = 0; i < n; i++)
  {
    y[i] = (double) i;
  }
  
  // Plus as "typical" binary operator
  auto plus = [] (auto x, auto y)
  {
    return x + y;
  };
  
  // Run serial/naive implementation
  std::cout << "Starting naive scan" << std::endl;
  std::chrono::duration<double, std::milli> timer_naive;
  for (int rep = 0; rep < nrep; rep++)
  {
    auto t1 = std::chrono::high_resolution_clock::now();
    naiveScan(x, y, plus);
    auto t2 = std::chrono::high_resolution_clock::now();
    timer_naive += t2 - t1;
    if (rep == 0)
    {
      check(y);
    }
  }
  
  // Run serial/std implementation
  std::cout << "Starting std scan (seq)" << std::endl;
  std::chrono::duration<double, std::milli> timer_seq;
  for (int rep = 0; rep < nrep; rep++)
  {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::inclusive_scan(std::execution::seq, x.begin(), x.end(), y.begin(), plus);
    auto t2 = std::chrono::high_resolution_clock::now();
    timer_seq += t2 - t1;
    if (rep == 0)
    {
      check(y);
    }
  }
  
  // Run parallel/std implementation
  std::cout << "Starting std scan (par)" << std::endl;
  std::chrono::duration<double, std::milli> timer_par;
  for (int rep = 0; rep < nrep; rep++)
  {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::inclusive_scan(std::execution::par, x.begin(), x.end(), y.begin(), plus);
    auto t2 = std::chrono::high_resolution_clock::now();
    timer_par += t2 - t1;
    if (rep == 0)
    {
      check(y);
    }
  }
  std::cout << "Starting std scan (par_unseq)" << std::endl;
  std::chrono::duration<double, std::milli> timer_par_unseq;
  for (int rep = 0; rep < nrep; rep++)
  {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::inclusive_scan(std::execution::par_unseq, x.begin(), x.end(), y.begin(), plus);
    auto t2 = std::chrono::high_resolution_clock::now();
    timer_par_unseq += t2 - t1;
    if (rep == 0)
    {
      check(y);
    }
  }

  // Output
  auto t_naive = timer_naive.count();
  auto t_seq = timer_seq.count();
  auto t_par = timer_par.count();
  auto t_par_unseq = timer_par_unseq.count();
  std::cout << "Timings (ms)" << std::endl
	    << "Naive: " << t_naive << std::endl
	    << "Seq: " << t_seq << std::endl
	    << "Par: " << t_par << std::endl
	    << "Par_Unseq: " << t_par_unseq << std::endl;
  
  return 0;
}
