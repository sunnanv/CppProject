#ifndef HIGH_LEVEL_ITERATOR_H
#define HIGH_LEVEL_ITERATOR_H
#include <iterator>

/** 
 * An random access iterator class. The high_level_iterator allows 
 * a user to iterate over two iterators
 * as if they where one. Does not copy the containers, it uses pointers.\n
 * T1 and T2 is the types of the containers (e.g vector<int>). They do not have to
 * be of the same type.
 */
template <typename T1, typename T2>
class high_level_iterator {
public:
	/**
	 * variables that an iterator needs to contain
	 */
	using value_type = typename T1::value_type;
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = typename T1::difference_type;
	using pointer = typename std::conditional<std::is_const<T1>::value, const value_type*, value_type*>::type;
	using reference = typename std::conditional<!std::is_const<T1>::value, value_type&, const value_type&>::type;


	/**
	 * Constructs an iterator over two containers.
	 * 
	 * @param f the first container to iterate over
	 * @param s the second container to iterate over
	 * @param start the position to where the iterator points
	 */
	high_level_iterator(T1* f, T2* s, unsigned int start=0): 
	first{f}, second{s}, firstSize{f->size()}, i{start}{}
	~high_level_iterator(){}

	/**
	 * Assignment operator.
	 * @param c Iterator to assign from
	 * @return a reference to this iterator.
	 */
	high_level_iterator<T1, T2>& operator=(const high_level_iterator<T1, T2>& c)
	{
		first = (c.first);
		second = (c.second);
		firstSize = c.firstSize;
		i = c.i;
		return (*this);
	}

	/* INCREMENT AND DECREMENT OPERATORS */
	/**
	 * Prefix increment operator.
	 * @return a reference to this incremented iterator.
	 */
	high_level_iterator<T1, T2>& operator++(){ ++i; return (*this);};
	/**
	 * Postfix increment operator.
	 * @return a reference to this iterator before increment.
	 */
	high_level_iterator<T1, T2> operator++(int){auto temp(*this); ++i; return temp;}

	/**
	 * Prefix decrement operator.
	 * @return a reference to this decremented iterator.
	 */
	high_level_iterator<T1, T2>& operator--(){ --i; return (*this);};

	/**
	 * Postfix decrement operator.
	 * @return a reference to this iterator before decrement.
	 */
	high_level_iterator<T1, T2> operator--(int){ auto temp(*this); --i; return temp;};


	/* COMPOUND ASSIGNMENT OPERATORS */
	/**
	 * Addition assignment operator. Allows incrementing multiple steps in constant time.
	 * @param rhs the amount of steps to go forward (the right hand side of +=)
	 * @return a reference to this iterator after increment
	 */
	high_level_iterator<T1, T2>& operator+=(const difference_type rhs) {i += rhs; return *this;};

	/**
	 * Subtraction assignment operator. Allows decrementeing multiple steps in constant time.
	 * @param rhs the amount of steps to go backward (the right hand side of -=)
	 * @return a reference to this iterator after decrement
	 */
	high_level_iterator<T1, T2>& operator-=(const difference_type rhs) {i -= rhs; return *this;};


	/* ARITHMETIC OPERATORS */
	/**
	 * Addition operator. Allows assigning auto a = iterator + 5
	 * @param rhs the amount of steps to increment from this one.
	 * @return a new high_level_iterator incremented rhs steps from this one.
	 */
	high_level_iterator<T1, T2> operator+(const difference_type rhs) const {high_level_iterator<T1, T2> temp = *this; temp += rhs; return temp;};
	
	/**
	 * Subtraction operator. Allows assigning auto a = iterator - 5
	 * @param rhs the amount of steps to decrement from this one.
	 * @return a new high_level_iterator decremented rhs steps from this one.
	 */
	high_level_iterator<T1, T2> operator-(const difference_type rhs) const {high_level_iterator<T1, T2> temp = *this; temp -= rhs; return temp;};
	
	/**
	 * Distance operator. Gives the distance between this iterator and an other.
	 * @param rhs Iterator to calcuate distance from.
	 * @return the distance between this iterator and rhs.
	 */
	difference_type operator-(const high_level_iterator<T1, T2>& rhs) const {return i-rhs.i;};

	/**
	 * Addition operator. Allows assigning auto a = 5 + iterator
	 * @param lhs the amount of steps to increment from this one.
	 * @param rhs the iterator to increment from (this one)
	 * @return a new high_level_iterator incremented lhs steps from this one
	 */
	friend high_level_iterator<T1, T2> operator+(difference_type lhs, const high_level_iterator<T1, T2>& rhs) 
	{
		high_level_iterator<T1, T2> temp = rhs;
		temp += lhs;
		return temp;
	}


	/* REFERENCE OPERATORS */
	/**
	 * Reference operator. Makes it possible to get the value from the iterator (*iterator)
	 * @return A reference to the value this iterator is pointing to
	 */
	reference operator*()
	{ 
		if(i < firstSize)
		{
			return (*first)[i]; 
		} else
		{
			return (*second)[i-firstSize]; 
		}
	}

	/* RELATIONAL OPERATORS */
	/**
	 * Equals operator. Allows comparing this iterator to another.
	 * @param rhs the iterator to compare to
	 * @return true if they are equal, otherwise false.
	 */
	bool operator==(const high_level_iterator<T1, T2>& rhs) {return i == rhs.i;};

	/**
	 * Not-equals operator. Allows comparing this iterator to another.
	 * @param rhs the iterator to compare to
	 * @return true if they are not equal, otherwise false.
	 */
	bool operator!=(const high_level_iterator<T1, T2>& rhs) { return i != rhs.i;};

	/**
	 * Less-than operator. Allows comparing this iterator with another to see which one is first (lesser)
	 * @param rhs Iterator to compare to.
	 * @return true if this iterator is less than rhs, else false.
	 */
	bool operator<(const high_level_iterator<T1, T2>& rhs){return i<rhs.i;};

	/**
	 * Greater-than operator. Allows comparing this iterator with another to see which one is last (greater)
	 * @param rhs Iterator to compare to.
	 * @return true if this iterator is greater than rhs, else false.
	 */
	bool operator>(const high_level_iterator<T1, T2>& rhs){return i>rhs.i;};

	/**
	 * Lesser-than-or-equal operator. Allows comparing this iterator with another to see which one is first (lesser)
	 * @param rhs Iterator to compare to.
	 * @return true if this iterator is lesser than or equal to rhs, else false.
	 */
	bool operator<=(const high_level_iterator<T1, T2>& rhs){return i<=rhs.i;};

	/**
	 * Greater-than-or-equal operator. Allows comparing this iterator with another to see which one is last (greater)
	 * @param rhs Iterator to compare to.
	 * @return true if this iterator is greater than or equal to rhs, else false.
	 */
	bool operator>=(const high_level_iterator<T1, T2>& rhs){return i>=rhs.i;};


private:
	T1* first;
	T2* second;
	size_t firstSize;
	unsigned int i;
};


#endif