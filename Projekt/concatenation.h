#ifndef CONCATENATION_H
#define CONCATENATION_H

#include "high_level_iterator.h"
#include <iostream>
#include <array>
#include <algorithm>
#include <initializer_list>

template <typename V, typename... T>
constexpr auto array_of(T&&... t)
    -> std::array < V, sizeof...(T) >
{
    return {{ std::forward<T>(t)... }};
}

/*template <typename V>
constexpr auto mkarray(std::initializer_list<V> l)
	-> std::array < V, l.size() >
	{
		return {{std::forward<T>(t)}}
	}
*/
template <typename T1, typename T2>
class concatenation{
	
	friend high_level_iterator<typename T1::iterator, T1, T2>;
public:
	using value_type = typename T1::value_type;
	using iter = high_level_iterator<typename T1::iterator, T1, T2>;
	concatenation(T1& a, T2& b): first{&a}, second{&b}{};

	iter begin() {return iter(first, second, first->size(), 0);};
	iter end(){return iter(first, second, first->size(), first->size()+second->size());};
	
private:
	T1 *first;
	T2 *second;
};

#endif