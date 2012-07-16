/*
 * ArrayNBase.h
 *
 *  Created on: Jul 10, 2012
 *      Author: Chris
 */

#ifndef ARRAYBASE_H_
#define ARRAYBASE_H_

#include "Types.h"
#include <memory>
#include <assert.h>
#include <typeinfo>

namespace linear_algebra {
namespace array {
namespace base {

template<typename T, std::size_t N>
class Array;
template<typename T, std::size_t N>
class ConstArrayProxy;
template<typename T, std::size_t N>
class ArrayProxy;




/** Data typedef for use with Arrays
 *
 */
template<typename T>
struct ArrayTypes{
	typedef std::size_t Size;
	typedef Size Index;
	typedef T* TPtr;
	typedef const T* ConstTPtr;
	typedef Size* SizePtr;
	typedef const Size* ConstSizePtr;
};

/** N dimensional array accessor
 * 	Acts as a base class for N dimensional arrays allowing nested operator[] overloading
 * 	to access data.  Cannot be instantiated as constructors are protected.
 */
template<typename T, std::size_t N>
class Accessor
: public ArrayTypes<T>
  {
	typedef ArrayTypes<T> Super;
  public:
	// Inherited types
	typedef typename Super::Size Size;
	typedef typename Super::Index Index;
	typedef typename Super::TPtr TPtr;
	typedef typename Super::ConstTPtr ConstTPtr;
	typedef typename Super::SizePtr SizePtr;
	typedef typename Super::ConstSizePtr ConstSizePtr;


	typedef ArrayProxy<T,N-1> Reference;
	typedef ConstArrayProxy<T,N-1> ConstReference;

  protected:
	/** Template array access function, takes a reference type as a parameter for return.
	 *	ReferenceType can be SubArray<T,N-1> or ConstSubArray<T,N-1>
	 */
	template<typename ReferenceType>
	ReferenceType access( types::TypeParameter<ReferenceType>, TPtr head, SizePtr strides, Index index){
		assert( (typeid(ReferenceType)==typeid(Reference)) || (typeid(ReferenceType)==typeid(ConstReference)) );
		TPtr newhead = head + strides[0]*index;
		return ReferenceType(newhead, strides+1);
	}
	Accessor(){}
	~Accessor(){}
  };


/** Template specialization for 1 dimensional array Accessor
 *
 */
template<typename T>
class Accessor<T,1>
: public ArrayTypes<T>
  {
	typedef ArrayTypes<T> Super;
  public:
	// Inherited types
	typedef typename Super::Size Size;
	typedef typename Super::Index Index;
	typedef typename Super::TPtr TPtr;
	typedef typename Super::ConstTPtr ConstTPtr;
	typedef typename Super::SizePtr SizePtr;
	typedef typename Super::ConstSizePtr ConstSizePtr;

	typedef T& Reference;
	typedef const T& ConstReference;

  public:
	/** Template array access function, takes a reference type as a parameter for return.
	 *  ReferenceType can be T& or const T&
	 */
 	template<typename ReferenceType>
	ReferenceType access(types::TypeParameter<ReferenceType>, TPtr head, SizePtr strides, Index index){
		assert( (typeid(ReferenceType)==typeid(Reference)) || (typeid(ReferenceType)==typeid(ConstReference)) );
		return head[index];
	}
	Accessor(){}
	~Accessor(){}
  };


// Intermediate Accessor class template to avoid template compilation size errors due to nesting std::size_t
template<typename T, class N>
struct AccessorType
{
	static const std::size_t DIMENSION = N::Value;
	typedef Accessor<T,DIMENSION> Type;
};

/**
 * Base class for N dimensional array
 * Inherits from N dimensional Accessor chosen by AccessorType<T,N>::Type
 * Implements nested operator[] element access
 */
template<typename T, std::size_t N>
class ArrayBase
: public AccessorType<T,types::SizeType<N>>::Type
  {
  public:
	typedef typename AccessorType<T,types::SizeType<N> >::Type Super;
  public:
	// Inherited types
	typedef typename Super::Size Size;
	typedef typename Super::Index Index;
	typedef typename Super::TPtr TPtr;
	typedef typename Super::ConstTPtr ConstTPtr;
	typedef typename Super::SizePtr SizePtr;
	typedef typename Super::ConstSizePtr ConstSizePtr;
	typedef typename Super::Reference Reference;
	typedef typename Super::ConstReference ConstReference;

  };


template<typename T, std::size_t N>
class ConstArrayProxy
: public ArrayBase<T,N>
  {
	typedef ArrayBase<T,N> Super;
  public:
	// Inherited types
	typedef typename Super::Size Size;
	typedef typename Super::Index Index;
	typedef typename Super::TPtr TPtr;
	typedef typename Super::ConstTPtr ConstTPtr;
	typedef typename Super::SizePtr SizePtr;
	typedef typename Super::ConstSizePtr ConstSizePtr;
	typedef typename Super::Reference Reference;
	typedef typename Super::ConstReference ConstReference;

	ConstArrayProxy(TPtr head, SizePtr strides)
	: _head(head),
	  _strides(strides)
	{

	}
	~ConstArrayProxy(){}

	Reference operator[](Index index){return Super::access(types::TypeParameter<Reference>(), this->_head,this->_strides,index);}
	ConstReference operator[](Index index)const{return Super::access(types::TypeParameter<Reference>(), this->_head,this->_strides,index);}
  protected:
	ConstTPtr _head;
	SizePtr _strides;
  };

template<typename T, std::size_t N>
class ArrayProxy
: public ArrayBase<T,N>
  {
	typedef ArrayBase<T,N> Super;
  public:
	// Inherited types
	typedef typename Super::Size Size;
	typedef typename Super::Index Index;
	typedef typename Super::TPtr TPtr;
	typedef typename Super::ConstTPtr ConstTPtr;
	typedef typename Super::SizePtr SizePtr;
	typedef typename Super::ConstSizePtr ConstSizePtr;
	typedef typename Super::Reference Reference;
	typedef typename Super::ConstReference ConstReference;

	ArrayProxy(TPtr head, SizePtr strides)
	: _head(head),
	  _strides(strides)
	{

	}
	~ArrayProxy(){}

	Reference operator[](Index index){return Super::access(types::TypeParameter<Reference>(), this->_head,this->_strides,index);}
	ConstReference operator[](Index index)const{return Super::access(types::TypeParameter<Reference>(), this->_head,this->_strides,index);}
  protected:
	TPtr _head;
	SizePtr _strides;
  };

} /* namespace base */
} /* namespace array */
} /* namespace linear_algebra */
#endif /* ARRAYBASE_H_ */
