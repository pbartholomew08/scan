#ifndef __IMPL_H_
#define __IMPL_H_

#include <stdlib.h>
#include <vector>

template< class T, class BinaryOperator>
void naiveScan(std::vector<T> &x, std::vector<T> &y,
	       BinaryOperator op);

#endif
