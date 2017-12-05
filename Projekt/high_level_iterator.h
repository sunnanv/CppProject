#ifndef HIGH_LEVEL_ITERATOR_H
#define HIGH_LEVEL_ITERATOR_H

#include <iterator>
#include <iostream>
#include <climits>

template <typename Iterator, typename T1, typename T2>
class high_level_iterator {
public:
	using value_type = typename Iterator::value_type;
	using iterator_category = std::input_iterator_tag;
	using difference_type = typename Iterator::difference_type;
	using pointer = value_type*;
	using reference = value_type&;


	high_level_iterator(T1* f, T2* s, unsigned int fsize, unsigned int start=0): 
	first{f}, second{s}, firstSize{fsize}, i{start} {};

	high_level_iterator& operator++(){ ++i; return (*this);};
	high_level_iterator& operator++(int){auto temp(*this); ++i; return temp;}

	value_type operator*()
	{ 
		if(i < firstSize)
		{
			return first->at(i); 
		} else 
		{
			return second->at(i-firstSize); 
		} 
	};

	bool operator==(const high_level_iterator<Iterator, T1, T2>& rhs) 
	{
		return getV() == rhs.getV(); 
	}
	bool operator!=(const high_level_iterator<Iterator, T1, T2>& rhs) 
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