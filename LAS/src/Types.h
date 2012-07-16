/*
 * Types.h
 *
 *  Created on: Jul 7, 2012
 *      Author: Chris
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <cstddef>
#include <vector>


namespace types {

template<bool Condition, typename T1, typename T2>
struct ConditionalType{	typedef T1 Type; };
template<typename T1, typename T2>
struct ConditionalType<false,T1,T2>{ typedef T2 Type;};

// Simple size_t wrapper
template<std::size_t N>
struct SizeType{
	typedef std::size_t Type;
	static const Type Value = N;
};

// Wrapper for passing a type as a function or template parameter
template<typename T>
struct TypeParameter {};


} /* namespace types */

#endif /* TYPES_H_ */

