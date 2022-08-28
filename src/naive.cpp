/*
 *        FILE: naive.cpp
 * DESCRIPTION: Provides a naive implementation of scan.
 */

#include "implementations.h"

void naiveScan(std::vector<T> &x, std::vector<T> &y,
			   BinaryOperator op)
{
  // Determine size of scan
  auto nx = x.size();
  auto ny = y.size();
  auto n = min(nx, ny);

  y[0] = x[0]; // Initialise the scan
  
  for(std::vector<T>::size_type i = 1; i < n; i++)
  {
    y[i] = op(y[i - 1], x[i]);
  }
  
  return y;
}
