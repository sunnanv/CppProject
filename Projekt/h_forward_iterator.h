#ifndef H_FORWARD_ITERATOR_H
#define H_FORWARD_ITERATOR_H

#include <iterator>
#include <iostream>
#include <climits>

template <typename T1, typename T2>
class h_forward_iterator {
public:
	using value_type = typename T1::value_type;
	using iterator_category = std::forward_iterator_tag;
	using difference_type = typename T1::difference_type;
	using pointer = value_type*;
	using reference = value_type&;


	h_forward_iterator(T1* f, T2* s, unsigned int fsize, unsigned int start=0): 
	first{f}, second{s}, firstSize{fsize}, i{start} {};

	h_forward_iterator& operator++(){ ++i; return (*this);};
	h_forward_iterator& operator++(int){auto temp(*this); ++i; return temp;}

	value_type& operator*()
	{ 
		if(i < firstSize)
		{
			return first->at(i); 
		} else 
		{
			return second->at(i-firstSize); 
		} 
	};

	bool operator==(const h_forward_iterator<T1, T2>& rhs) 
	{
		return getV() == rhs.getV(); 
	}
	bool operator!=(const h_forward_iterator<T1, T2>& rhs) 
	{ 
		return getV() != rhs.getV();
	}

	const value_type* getV() const
	{
		if(i < firstSize)
		{
			return &((*first)[i]);
		} else 
		{
			return &((*second)[i]);
		}
	}

	
private:
	T1* first;
	T2* second;
	unsigned int firstSize;
	unsigned int i;
};


#endif