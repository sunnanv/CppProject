#ifndef CONCATENATION_H
#define CONCATENATION_H

//#include "h_forward_iterator.h"
#include "high_level_iterator.h"
#include <iostream>
#include <array>
#include <algorithm>
#include <initializer_list>

template <typename T1, typename T2>
class concatenation{
	
	//friend h_forward_iterator<T1, T2>;
	
	friend high_level_iterator<T1, T2>;
public:
	using value_type = typename T1::value_type;
	
	//using iter = h_forward_iterator<T1, T2>;
	using iter = high_level_iterator<T1, T2>;
	using iter_const = high_level_iterator<const T1, const T2>;
	
	concatenation(T1& a, T2& b): first{&a}, second{&b}{};
	~concatenation(){};

	iter begin() {return iter(first, second, first->size(), 0);};
	iter end(){return iter(first, second, first->size(), first->size()+second->size());};
	
	iter_const begin() const{return cbegin();}
	iter_const end() const{return cend();}
	iter_const cbegin(){return iter_const(first, second, first->size(), 0);};
	iter_const cend(){return iter_const(first, second, first->size(), first->size()+second->size());};
private:
	T1 *first;
	T2 *second;
};

#endif