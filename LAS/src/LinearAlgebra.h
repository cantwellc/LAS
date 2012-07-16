/*
 * LinearAlgebraSubroutines.h
 *
 *  Created on: Jul 15, 2012
 *      Author: Chris
 */

#ifndef LINEARALGEBRA_H_
#define LINEARALGEBRA_H_

#include "Array.h"

namespace linear_algebra {

template<typename T>
class Vector : public array::Array<T,1>{};

template<typename T>
class Matrix
: public array::Array<T,2>
  {
	typedef array::Array<T,2> Super;
  public:
	template<typename Dimensions>
	Matrix(Dimensions dimensions)
	: Super(dimensions)
	  {

	}
  };

/**
 * Base class declaring common linear algebra subroutines.
 */
class Subroutines {
public:
	Subroutines();
	virtual ~Subroutines();
};

} /* namespace linear_algebra */
#endif /* LINEARALGEBRA_H_ */
