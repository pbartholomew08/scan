
#include "implementations.h"

int main()
{
  int nrep = 10;
  
  // Plus as "typical" binary operator
  auto plus = [] (auto x, auto y)
  {
    return x + y;
  };
  
  // Run serial/naive implementation
  std::cout << "Starting naive scan" << std::endl;
  auto timer_naive = std::chrono::high_resolution_clock::now();
  for (int rep = 0; rep < nrep; rep++)
  {
    auto t1 = std::chrono::high_resolution_clock::now();
    naiveScan(x, y, plus);
    auto t2 = std::chrono::high_resolution_clock::now();
    timer_naive += t2 - t1;
    check(y);
  }
  
  // Run serial/std implementation
  std::cout << "Starting std scan (seq)" << std::endl;
  auto timer_seq = std::chrono::high_resolution_clock::now();
  for (int rep = 0; rep < nrep; rep++)
  {
    auto t1 = std::chrono::high_resolution_clock::now();
    inclusive_scan(std::execution::seq, x.begin(), x.end(), y.begin(), plus);
    auto t2 = std::chrono::high_resolution_clock::now();
    timer_seq += t2 - t1;
    check(y);
  }
  
  // Run parallel/std implementation
  std::cout << "Starting std scan (par)" << std::endl;
  auto timer_par = std::chrono::high_resolution_clock::now();
  for (int rep = 0; rep < nrep; rep++)
  {
    auto t1 = std::chrono::high_resolution_clock::now();
    inclusive_scan(std::execution::par, x.begin(), x.end(), y.begin(), plus);
    auto t2 = std::chrono::high_resolution_clock::now();
    timer_par += t2 - t1;
    check(y);
  }
  std::cout << "Starting std scan (par_unseq)" << std::endl;
  auto timer_par_unseq = std::chrono::high_resolution_clock::now();
  for (int rep = 0; rep < nrep; rep++)
  {
    auto t1 = std::chrono::high_resolution_clock::now();
    inclusive_scan(std::execution::par_unseq, x.begin(), x.end(), y.begin(), plus);
    auto t2 = std::chrono::high_resolution_clock::now();
    timer_par_unseq += t2 - t1;
    check(y);
  }

  // Output
  auto t_naive = std:chrono::microseconds(timer_naive).count();
  auto t_seq = std:chrono::microseconds(timer_seq).count();
  auto t_par = std:chrono::microseconds(timer_par).count();
  auto t_par_unseq = std:chrono::microseconds(timer_par_unseq).count();
  std::cout << "Timings (us)" << std::endl
	    << "Naive: " << t_naive << std::endl
	    << "Seq: " << t_seq << std::endl
	    << "Par: " << t_par << std::endl
	    << "Par_Unseq: " << t_par_unseq << std::endl;
  
  return 0;
}

void check(std::vector<T> &y)
{
  for (std::vector<T>::size_type i = 1; i < n; i++)
  {
    auto yp = y[i - 1];
    auto yc = y[i];
    if (yc <= yp)
    {
      std::cout << "ERROR: " << yc << " should be > " << yp << std::endl;
      exit(1);
    }
  }
}
