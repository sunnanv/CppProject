#ifndef CONCATENATION_H
#define CONCATENATION_H

#include "high_level_iterator.h"

/**
 * A class for concatenation two containers without copying them.
 * After concatenation it is possible to iterate over the containers
 * as if they where one. Supports const containers. \n
 * T1 and T2 is the types of the two containers (they do not need to be of the same type).
 */
template <typename T1, typename T2>
class concatenation{

	friend high_level_iterator<T1, T2>;

public:
	
	using iter = high_level_iterator<T1, T2>;
	using iter_const = high_level_iterator<const T1, const T2>;
	
	/**
	 * Creates a concatenation object that points to two containers.
	 */
	concatenation(T1& a, T2& b): first{&a}, second{&b}{};
	~concatenation(){};

	/**
	 * Returns an iterator pointing to the first element in the first container.
	 */
	iter begin() {return iter(first, second, 0);};

	/**
	 * Returns an iterator pointing to the last element in the second container.
	 */
	iter end(){return iter(first, second, first->size()+second->size());};
	
	/**
	 * Returns a constant iterator pointing to the first element in the first container.
	 * Is called when T1 and T2 is of const type.
	 */
	iter_const begin() const{return cbegin();}
	/**
	 * Returns an iterator pointing to the last element in the second container.
	 * Is called when T1 and T2 is of const type.
	 */
	iter_const end() const{return cend();}

	/**
	 * Returns a constant iterator pointing to the first element in the first container.
	 */
	iter_const cbegin(){return iter_const(first, second, 0);};
	/**
	 * Returns a constant iterator pointing to the first element in the first container.
	 */
	iter_const cend(){return iter_const(first, second, /*first->size(),*/ first->size()+second->size());};
private:
	T1 *first;
	T2 *second;
};

#endif