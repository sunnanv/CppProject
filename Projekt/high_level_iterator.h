#ifndef HIGH_LEVEL_ITERATOR_H
#define HIGH_LEVEL_ITERATOR_H

#include <iterator>
#include <iostream>
#include <climits>
//#include <conditional>
#include <type_traits>

template <typename T1, typename T2>
class high_level_iterator {
public:
	using value_type = typename T1::value_type;//typename std::conditional<std::is_const<typename T1::value_type>::value, const typename T1::value_type, T1::value_type>::type;
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = typename T1::difference_type;
	using pointer = typename std::conditional<std::is_const<T1>::value, const value_type*, value_type*>::type;
	using reference = typename std::conditional<!std::is_const<T1>::value, value_type&, const value_type&>::type;


	high_level_iterator(T1* f, T2* s, unsigned int fsize, unsigned int start=0): 
	first{f}, second{s}, firstSize{fsize}, i{start}{}
	high_level_iterator(const high_level_iterator& c) = default;

	~high_level_iterator(){}

	high_level_iterator<T1, T2>& operator=(const high_level_iterator<T1, T2>& c) = default;
	high_level_iterator<T1, T2>& operator=(high_level_iterator<T1, T2>& c)
	{
		first = (c.first);
		second = (c.second);
		firstSize = c.firstSize;
		i = c.i;
		return (*this);
	}

	high_level_iterator<T1, T2>& operator++(){ ++i; return (*this);};
	high_level_iterator<T1, T2>& operator++(int){auto temp(*this); ++i; return temp;}

	high_level_iterator<T1, T2>& operator--(){ --i; return (*this);};
	high_level_iterator<T1, T2>& operator--(int){ auto temp(*this); --i; return temp;};

	high_level_iterator<T1, T2>& operator+=(const difference_type rhs) {i += rhs; return *this;};
	high_level_iterator<T1, T2>& operator-=(const difference_type rhs) {i -= rhs; return *this;};
	high_level_iterator<T1, T2> operator+(const difference_type rhs) const {high_level_iterator<T1, T2> temp = *this; temp += rhs; return temp;};
	high_level_iterator<T1, T2> operator-(const difference_type rhs) const {high_level_iterator<T1, T2> temp = *this; temp -= rhs; return temp;};
	friend high_level_iterator<T1, T2> operator+(difference_type lhs, const high_level_iterator<T1, T2>& rhs) 
	{
		high_level_iterator<T1, T2> temp = rhs;
		temp += lhs;
		return temp;
	}

	difference_type operator-(const high_level_iterator<T1, T2>& rhs) const {return i-rhs.i;}
	reference operator*()
	{ 
		if(i < firstSize)
		{
			return (*first)[i]; 
		} else// if( i < (firstSize + second->size()))
		{
			return (*second)[i-firstSize]; 
		} //else {
			//return *second->end();
		//}
	};

	/*const value_type& operator*() const
	{ 
		if(i < firstSize)
		{
			const value_type& cref = (*first)[i];

			return cref; 
		} else// if( i < (firstSize + second->size()))
		{
			const value_type& cref = (*second)[i];
			return cref;
			//return std::const_cast<const reference>((*second)[i-firstSize]); 
		} //else {
			//return *second->end();
		//}
	}; */

	bool operator==(const high_level_iterator<T1, T2>& rhs) 
	{
		return i == rhs.i; 
	}
	bool operator!=(const high_level_iterator<T1, T2>& rhs) 
	{ 
		return i != rhs.i;
	}

	bool operator<(const high_level_iterator<T1, T2>& rhs){return i<rhs.i;};
	bool operator>(const high_level_iterator<T1, T2>& rhs){return i>rhs.i;};
	bool operator<=(const high_level_iterator<T1, T2>& rhs){return i<=rhs.i;};
	bool operator>=(const high_level_iterator<T1, T2>& rhs){return i>=rhs.i;};

	pointer getV() const
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
	//value_type last;
};


#endif