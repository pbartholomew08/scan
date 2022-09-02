/*
 * FILE: implementations.h
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __IMPL_H_
#define __IMPL_H_

#include <vector>

template< class T, class BinaryOperator >
void naiveScan(std::vector<T> &x, std::vector<T> &y,
	       BinaryOperator op)
{
  // Determine size of scan
  auto nx = x.size();
  auto ny = y.size();
  auto n = std::min(nx, ny);

  y[0] = x[0]; // Initialise the scan
  
  for(int i = 1; i < n; i++)
  {
    y[i] = op(y[i - 1], x[i]);
  }
}

template< class T >
void check(std::vector<T> &y)
{
  for (int i = 1; i < y.size(); i++)
  {
    auto yp = y[i - 1];
    auto yc = y[i];
    if (yc <= yp)
    {
      std::cout << "ERROR: " << yc << " should be > " << yp << std::endl;
      exit(1);
    }
  }
  std::cout << "Check success" << std::endl;
}

#endif
