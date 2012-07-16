/*
 * Array.h
 *
 *  Created on: Jul 13, 2012
 *      Author: Chris
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include "ArrayBase.h"
#include <assert.h>
#include <memory>

namespace linear_algebra{
namespace array{

/**
 * N-Dimensional array class.
 * The array object owns pointers to its data. (create and delete)
 * Array proxies returned by operator[] do not own pointers to their data
 *    but point to the same data as the full Array object.  Any changes performed
 *    on data in the proxy is reflected in the Array.
 */
template<typename T, std::size_t N>
class Array
: public base::ArrayBase<T,N>
  {
	typedef base::ArrayBase<T,N> Super;
  public:
	typedef typename Super::Size Size;
	typedef typename Super::Index Index;
	typedef typename Super::Reference Reference;
	typedef typename Super::ConstReference ConstReference;

	typedef T* TPtr;
	typedef Size* SizePtr;

	static const Size DIMENSIONALITY = N;


	/**
	 * Template constructor.  Takes an object that describes the size of each dimension.
	 * Dimensions object must implement size() and operator[] element access.
	 */
	template<typename Dimensions>
	Array(Dimensions dimensions){
//		assert((dimensions.size()==DIMENSIONALITY) && (DIMENSIONALITY > 0));
		Size size = 1;
		// strides will be an N-1 dimensional array holding the distance between the heads of each
		// subarray.  For example, strides[0] is the number of elements in each of the
		// dimensions[0] subarrays of dimensionality N-1.
		SizePtr strides = new Size[DIMENSIONALITY-1];
		SizePtr dim = new Size[DIMENSIONALITY];
		// Build up the array of strides from the bottom.
		for(unsigned int i=DIMENSIONALITY-1;i>0;--i){
			dim[i]=dimensions[i];
			size = size*dimensions[i];
			strides[i-1]=size;
		}
		dim[0]=dimensions[0];
		size = size*dimensions[0];
		TPtr head = new T[size];
		this->_head = head;
		this->_dimensions = dim;
		this->_size = size;
		this->_strides = strides;
	}

	~Array(){
		delete[] _strides;
		delete[] _head;
	}

	/* Returns a pointer to the head of the contiguous block of data stored by the array. */
	TPtr data(void){return this->_head;}
	/* Returns the total number of elements in the array. */
	Size& size(void){return this->_size;}
	/* Returns the size of a particular dimension of the array */
	Size& size(Index dimension){return this->_dimensions[dimension];}

	Reference operator[](Index index){return Super::access(types::TypeParameter<Reference>(), this->_head,this->_strides,index);}
	ConstReference operator[](Index index)const{return Super::access(types::TypeParameter<Reference>(), this->_head,this->_strides,index);}
  protected:
	TPtr _head;
	SizePtr _dimensions;
 	Size _size;
	SizePtr _strides;
 };


} // namespace array
} // namespace linear_algebra



#endif /* ARRAY_H_ */
