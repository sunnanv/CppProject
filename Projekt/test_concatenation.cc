/**
 * A class for testing concatenation and high_level_iterator.
 */

#include "concatenation.h"
#include <iostream>
#include <string>
#include <sstream>

#include <array>
#include <vector>
#include <deque>

#include <algorithm>
#include <numeric>


using std::cout;
using std::endl;

using std::string;

using std::vector;
using std::array;
using std::deque;

int i_find[2] = {5, 13};
string s_find[2] = {"a", "on"};


/**
 * Help method for printing to console.\n
 * Prints the title of what you test.
 * @param name the name of the thing you test (e.g vector)
 */
void printTitle(string name)
{
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	string s = "|" + name + ":";
	s.append(41-s.size(),' ');
	cout << s + "|\n";
}

/**
 * Help method for printing to console.\n
 * Prints the name of a subtest and if it passed or failed.
 * @param name the name of the subtest
 * @param passed true if the subtest passed, else false.
 */
void printTest(string name, bool passed)
{
	string s = "|  " + name + ":";
	s.append(passed? " PASSED" : " FAILED");
	s.append(41-s.size(), ' ');
	cout << s + "|\n";
}

/**
 * Help method for printing to console.\n
 * Used if a test fails, and prints out why.
 * @param why a string describing why the test failed
 */
void printFail(string why)
{
	if(why == "") return;
	string s = "|      ";
	int pos = 0;
	int remain = why.size();
	while(remain >= 31)
	{
		s.append(why, pos, 31);
		s.append("   |\n|      ");
		remain -= 31;
		pos += 31;
	}
	if(remain > 0)
	{
		s.append(why, pos, 31);
		s.append(31	-remain, ' ');
		s.append("   |\n|      ");
	}

	s.erase(s.size()-7);
	std::cout << s;
}

/**
 * Help method for printing to console.\n
 * Prints the end of what you test, with information
 * about how many subtest was successful and how many there was i total.
 * @param total total amount of subtests
 * @param success amount of successful subtests
 */
void printEnd(int total, int success)
{
	string s = "|";
	s.append(40, '-');
	s.append("|\n|");
	int tsize = total > 9? 2 : 1;
	int ssize = success > 9? 2 : 1;

	int half = (22-tsize-ssize)/2;
	s.append(half, ' ');
	s.append(std::to_string(success) + "/" + std::to_string(total) + " tests successful");
	s.append(half, ' ');
	s.append("|\n");

	s.append("|");
	s.append(40, '-');
	s.append("|");

	std::cout << s + "\n";
}

/**
 * Creates a string from any type that
 * has operator<< implemented.\n
 * T is the type that should be casted.
 * @param in the element to cast to string
 */
template<typename T>
std::string toString(T& in)
{
	std::stringstream rtrn;
	rtrn << std::noskipws << in;
	return rtrn.str();
}



/** 
 * Template struct for testing concatenation for two containers.
 * T1 and T2 is the types of the containers. They do not have to
 * be of the same type.
 */
template<typename T1, typename T2>
struct test {

	/** 
	 * #### Tests the iterator. \n
	 * Tests finding items in the concatenation and then copying from it.\n
	 * Tests normal iteration through the concatenation (auto it = conc.begin(); it != conc.end(); ++it)\n
	 * Tests rangefor-iteration (auto it : conc)\n
	 * Tests backwards iteration (--it)
	 *
	 * @param name what the console should output for this subtest
	 * @param first the first container that should be concatenated
	 * @param second the second container that should be concatenated
	 * @param find A vector that contains two elements that should be searched
	 * for with std::find.
	 */
	bool iterator(string name, T1& first, T2& second, typename T1::value_type find[])
	{
		bool success = true;
		string why = "";
		concatenation<T1, T2> conc(first, second);

		/* Get the correct elements and put them in T1 containers
		 * for checking during test */
		vector<typename T1::value_type> correct_full;
		std::copy(first.begin(), first.end(), back_inserter(correct_full));
		std::copy(second.begin(), second.end(), back_inserter(correct_full));

		auto start_c = std::find(correct_full.begin(), correct_full.end(), find[0]);
		auto stop_c = std::find(correct_full.begin(), correct_full.end(), find[1]);
		vector<typename T1::value_type> correct_part;
		std::copy(start_c, stop_c, back_inserter(correct_part));


		/* Test if copy is working */
		auto start = std::find(conc.begin(), conc.end(), find[0]);
		auto stop = std::find(conc.begin(), conc.end(), find[1]);

		vector<typename T1::value_type> result;
		std::copy(start, stop, std::back_inserter(result));
		size_t i1;
		for(i1 = 0; i1 != correct_part.size(); ++i1)
		{
			if(correct_part.at(i1) != result.at(i1))
			{
				string a = toString<typename T1::value_type>(result.at(i1));
				string b = toString<typename T1::value_type>(correct_part.at(i1));
				why = "(copy " + toString<size_t>(i1)  + ") (" + a + " != " + b + ")";
				success = false;
				break;
			}
		}

		size_t i2 = 0;
		if(success)
		{
			/* Test normal iteration */
			for(auto it = conc.begin(); it != conc.end(); ++it, ++i2)
			{
				if(correct_full.at(i2) != *it)
				{
					string a = toString<typename T1::value_type>(*it);
					string b = toString<typename T1::value_type>(correct_full.at(i2));
					why = "(iter " + std::to_string(i2) + ") (" + a + " != " + b + ")";
					success = false;
					break;
				}
			}
		}

		size_t i3 = 0;
		if(success)
		{
			/* Test rangefor iteration */
			for(auto it : conc)
			{
				if(correct_full.at(i3) != it)
				{	
					string a = toString<typename T1::value_type>(it);
					string b = toString<typename T1::value_type>(correct_full.at(i3));
					why = "(rangefor " + std::to_string(i3) + ") (" + a + " != " + b + ")";
					success = false;
					break;
				}
				++i3;
			}
		}

		size_t i4 = correct_full.size()-1;
		if(success)
		{
			for(auto it = --conc.end(); it != conc.begin(); --it)
			{
				if(correct_full.at(i4) != *it)
				{
					string a = toString<typename T1::value_type>(*it);
					string b = toString<typename T1::value_type>(correct_full.at(i4));
					why = "(back iter " + std::to_string(i4) + ") ("+ a + " != " + b + ")";
					success = false;
					break;
				}
				--i4;
			}
		}

		/* Check if everything is gone through */
		if(success && i1 != correct_part.size())
		{
			why = "(copy) (wrong amount of elements accessed, should be " + std::to_string(correct_part.size()) + ", is " + std::to_string(i1) + ")"; 
			success = false;
		}
		if(success && i2 != correct_full.size())
		{
			why = "(iter) (wrong amount of elements accessed, should be " + std::to_string(correct_full.size()) + ", is " + std::to_string(i2) + ")"; 
			success = false;
		}
		if(success && i3 != correct_full.size())
		{
			why = "(rangefor) (wrong amount of elements accessed, should be " + std::to_string(correct_full.size()) + ", is " + std::to_string(i3) + ")"; 
			success = false;
		}

		printTest(name, success);
		printFail(why);
		return success;
	}

	/** 
	 * #### Test for writing to the concatenation. \n
	 * ###### This test only works for containers with <int> due to iota. \n
	 * Tests writing with iota. \n
	 * Tests copying to the concatenation
	 * 
	 * @param name what the console should output for this subtest
	 * @param first the first container that should be concatenated
	 * @param second the second container that should be concatenated
	 */
	bool write_int(string name, T1 first, T2 second)
	{
		bool success = true;
		string why = "";
		concatenation<T1, T2> conc(first, second);

		/* Test writing to concatenation with iota (0,1,2,3,4,...)*/
		std::iota(conc.begin(), conc.end(), 0);
		int i1 = 0;
		for(auto it = conc.begin(); it != conc.end(); ++it)
		{
			if(*it != i1)
			{
				why = "(iota pos " + std::to_string(i1) + ") (wrong value, expected " + std::to_string(i1) + ", was " + std::to_string(*it) + ")";
				success = false;
				break;
			}
			++i1;
		}

		if(success)
		{
			/* Test writing to concatenation with copy (100,99,98,97,96,95) */
			vector<int> cop{100,99,98,97,96,95};
			auto noncop = std::find(conc.begin(), conc.end(), 6);
			std::copy(cop.begin(), cop.end(), conc.begin());
			std::copy(noncop, conc.end(), back_inserter(cop));
			int i2 = 0;
			for(auto i : conc)
			{
				if(cop.at(i2) != i)
				{
					why = "(copy, pos " + std::to_string(i2) + ") (wrong value, expected: " + std::to_string(cop.at(i2)) + ", was " + std::to_string(i) + ")";
					success = false;
					break;
				}
				++i2;
			}
		}
		printTest(name, success);
		printFail(why);
		return success;
	}

	/** #### Test sorting and reversing the concatenation.\n
	 * Tests sorting from smallest to largest.\n
	 * Tests sorting from largest to smallest.\n
	 * Tests reversing the concatenation.
	 *
	 * @param name what the console should output for this subtest
	 * @param first the first container that should be concatenated
	 * @param second the second container that should be concatenated
	 */
	bool sort(string name, T1 first, T2 second)
	{
		
		bool success = true;
		string why = "";

		vector<typename T1::value_type> correct_full;
		using type = typename T1::value_type;
		std::copy(first.begin(), first.end(), back_inserter(correct_full));
		std::copy(second.begin(), second.end(), back_inserter(correct_full));

		concatenation<T1, T2> conc(first, second);

		/* Test sorting concatenation with std::less (1,2,3,....) */
		std::sort(correct_full.begin(), correct_full.end(), std::less<type>());
		std::sort(conc.begin(), conc.end(), std::less<type>());

		int i1 = 0;
		for(auto i : conc)
		{
			if(correct_full.at(i1) != i)
			{
				string a = toString<type>(i);
				string b = toString<type>(correct_full.at(i1));
				why = "(sort less " + std::to_string(i1) + ") (" + a + " != " + b + ")";
				success = false;
				break;
			}
			++i1;
		}

		int i2 = 0;
		if(success)
		{
			/* Test sorting concatenation with std::greater (20, 19, 18, ...) */
			std::sort(correct_full.begin(), correct_full.end(), std::greater<type>());
			std::sort(conc.begin(), conc.end(), std::greater<type>());
			for(auto i : conc)
			{
				if(correct_full.at(i2) != i)
				{
					string a = toString<type>(i);
					string b = toString<type>(correct_full.at(i2));
					why = "(sort greater " + std::to_string(i2) + ") (" + a + " != " + b + ")";
					success = false;
					break;
				}
				++i2;
			}
		}

		int i3 = 0;
		if(success)
		{
			/* Test reversing concatenation */
			std::reverse(conc.begin(), conc.end());
			std::reverse(correct_full.begin(), correct_full.end());
			for(auto i : conc)
			{
				if(correct_full.at(i3) != i)
				{
					string a = toString<type>(i);
					string b = toString<type>(correct_full.at(i3));
					why = "(reverse " + std::to_string(i3) + ") (" + a + " != " + b + ")";
					success = false;
					break;
				}
				++i3;
			}

		} 

		printTest(name, success);
		printFail(why);
		return success;
	}

	/* #### Test for concatenation on constant containers.\n
	 * Tests so cbegin() and begin() on non-const concatenation is not the same type. \n
	 * Tests so cbegin() and begin() on const concatenation is of the same type. \n
	 * Tests so begin() on const concatenation is not the same type as begin() on non-const. \n
	 * Tests copy from const concatenation + rangefor-iteration. \n
	 * Tests normal iterator over constant concatenation.
	 *
	 * @param name what the console should output for this subtest
	 * @param first the first container that should be concatenated
	 * @param second the second container that should be concatenated
	 * @param find A vector that contains two elements that should be searched
	 */
	bool constCont(string name, T1 first, T2 second, typename T1::value_type find[])
	{

		vector<typename T1::value_type> correct_full;
		std::copy(first.begin(), first.end(), back_inserter(correct_full));
		std::copy(second.begin(), second.end(), back_inserter(correct_full));

		auto start_c = std::find(correct_full.begin(), correct_full.end(), find[0]);
		auto stop_c = std::find(correct_full.begin(), correct_full.end(), find[1]);
		vector<typename T1::value_type> correct_part;
		std::copy(start_c, stop_c, back_inserter(correct_part));


		bool success = true;
		string why = "";
		concatenation<T1,T2> conc_nonconst(first, second);
		concatenation<const T1, const T2> conc(first, second);

		/* Test if non-const begin and cbegin is of the same type (should not be) */
		if(std::is_same<decltype(conc_nonconst.begin()), decltype(conc_nonconst.cbegin())>::value)
		{
			why = "(non-const begin, cbegin) (No difference between nonconst begin() and cbegin())";
			success = false;
		}
		/* Test if const begin and const cbegin is of the same type (should be) */
		if(success && !std::is_same<decltype(conc.begin()), decltype(conc.cbegin())>::value)
		{
			why = "(const begin, cbegin) (begin() and cbegin() is not the same type.";
			success = false;
		}

		/* Test if const begin and non-const begin is of the same type (should not be) */
		if(success && std::is_same<decltype(conc.begin()), decltype(conc_nonconst.begin())>::value)
		{
			why = "(const vs non-const begin) (Same type between const and non-const begin()";
		}


		int i1 = 0;
		if(success)
		{
			/* Test copy from const container + foreach */
			auto start = std::find(conc.begin(), conc.end(), find[0]);
			auto end = std::find(conc.begin(), conc.end(), find[1]);
			vector<typename T1::value_type> result;
			std::copy(start, end, back_inserter(result));

			for(auto i : result)
			{
				if(i != correct_part.at(i1))
				{
					why = "(copy, foreach " + std::to_string(i1) + ")";
					success = false;
					break;
				}
				++i1;
			}
		}

		int i2 = 0;
		if(success)
		{
			/* Test normal iterator for const container */
			for(auto it = conc.begin(); it != conc.end(); ++it)
			{
				if(*it != correct_full.at(i2))
				{
					why = "(iter " + std::to_string(i2) + ")";
					success = false;
					break;
				}
				++i2;

			}
		}


		printTest(name, success);
		printFail(why);
		return success;
	}
	/**
	 * #### Test for the operators that should be present in an random access iterator.\n
	 * Tests preincrement (++it).\n
	 * Tests predecrement (--it).\n
	 * Tests addition assignment (it += n).\n
	 * Tests subtraction assignment (it -= n).\n
	 * Tests addition operator (it2 = it + n).\n
	 * Tests subtraction operator (it2 = it - n).\n
	 * Tests assignment operator (in those above, it2 = it (could add + n)).\n
	 * Tests postincrement (it++).\n
	 * Tests postdecrement (it--).\n
	 * Tests reference operator (*it).\n
	 * Tests relational operators (<, >, <=, >=, ==, !=).\n
	 * Tests distance operator (it1-it2).\n
	 *
	 * @param name what the console should output for this subtest
	 * @param first the first container that should be concatenated
	 * @param second the second container that should be concatenated
	 */
	bool operators(string name, T1 first, T2 second)
	{
		bool success = true;
		string why = "";
		vector<typename T1::value_type> correct;
		using type = typename T1::value_type;
		std::copy(first.begin(), first.end(), back_inserter(correct));
		std::copy(second.begin(), second.end(), back_inserter(correct));

		concatenation<T1, T2> conc(first, second);
		auto i1 = conc.begin();
		auto i1_c = correct.begin();

		++i1;
		++i1_c;

		if(*i1 != *i1_c)
		{
			why = "(pre ++ operator) (" + toString<type>(*i1) + " != " + toString(*i1_c);
			success = false;
		}

		--i1;
		--i1_c;

		if(success && *i1 != *i1_c)
		{
			why = "(pre -- operator) (" + toString<type>(*i1) + " != " + toString(*i1_c);
			success = false;
		}

		i1 += 3;
		i1_c += 3;

		if(success && *i1 != *i1_c)
		{
			why = "(+= operator) (" + toString<type>(*i1) + " != " + toString(*i1_c);
			success = false;
		}

		i1 -= 1;
		i1_c -= 1;

		if(success && *i1 != *i1_c)
		{
			why = "(-= operator) (" + toString<type>(*i1) + " != " + toString(*i1_c);
			success = false;
		}

		auto i2 = i1 + 2;
		auto i2_c = i1_c + 2;

		if(success && *i2 != *i2_c)
		{
			why = "(+ operator) (" + toString<type>(*i2) + " != " + toString(*i2_c);
			success = false;
		}


		i1 = i2 - 3;
		i1_c = i2_c - 3;

		if(success && *i1 != *i1_c)
		{
			why = "(- or = operator) (" + toString<type>(*i2) + " != " + toString(*i2_c);
			success = false;
		}


		i1--;
		i1_c--;

		if(success && *i1 != *i1_c)
		{
			why = "(post -- operator) (" + toString<type>(*i1) + " != " + toString(*i1_c);
			success = false;
		}

		i1++;
		i1_c++;

		if(success && *i1 != *i1_c)
		{
			why = "(post ++ operator) (" + toString<type>(*i1) + " != " + toString(*i1_c);
			success = false;
		}

		auto low = conc.begin() + 3;
		auto high = conc.end() - 4;
		auto low2 = conc.begin() +3;

		if(success && !(low < high)) {why = "(< operator)"; success = false;}
		if(success && (low > high)) {why = "(> operator)"; success = false;}
		if(success && !(low <= high) && !(low <= low2)) {why = "(<= operator)"; success = false;}
		if(success && (low >= high) && !(low >= low2)) {why = "(>= operator)"; success = false;}
		if(success && (low == high) && !(low == low2)) {why = "(== operator)"; success = false;}
		if(success && !(low != high) && (low != low2)) {why = "(!= operator)"; success = false;}

		if(i2-i1 != i2_c-i1_c) {why = ("iterator-iterator operator"); success = false;}


		printTest(name, success);
		printFail(why);
		return success;

	}
};

/**
 * #### Template method for running tests on containers (same or different type)
 * T1_int and T1_string is the same type with <int> or <string> (e.g vector<int> and vector<string>).\n
 * The same for T2_int and T2_string
 *
 * @param name what the test should be called in the output.
 * @param total the total amount of tests that have been run (adds to the value when done)
 * @param successful the total amount of tests that has been successful (adds to the value when done)
 */
template <typename T1_int, typename T1_string, typename T2_int, typename T2_string>
void container_test(string name, int& total, int& successful)
{
	vector<bool> test_result;
	printTitle(name);
	T1_int T1_i{1,2,3,4,5,6,7};
	T2_int T2_i{10,11,12,13,14};
	T1_string T1_s = {"this", "is", "a", "test", "for"};
	T2_string T2_s = {"concatenated containers", "on", "string", "container"};
	test<T1_int, T2_int> t_i;
	test<T1_string, T2_string> t_s; 
	test_result.push_back(t_i.iterator("test_iterator_int", T1_i, T2_i, i_find));
	test_result.push_back(t_s.iterator("test_iterator_string", T1_s, T2_s, s_find));
	test_result.push_back(t_i.write_int("test_write_int", T1_i, T2_i));
	test_result.push_back(t_i.sort("test_sort_int", T1_i, T2_i));
	test_result.push_back(t_s.sort("test_sort_string", T1_s, T2_s));
	test_result.push_back(t_i.constCont("test_const_int", T1_i, T2_i, i_find)); 
	test_result.push_back(t_i.constCont("test_const_string", T1_i, T2_i, i_find));
	test_result.push_back(t_i.operators("test_operators_int", T1_i, T2_i));
	test_result.push_back(t_s.operators("test_operators_string", T1_s, T2_s));
	int success = std::count(test_result.begin(), test_result.end(), true);

	total += test_result.size();
	successful += success;

	printEnd(test_result.size(),success);
}

/**
 * #### Template method for testing concateination between two containers of the same type.
 * Calls container_test with four types (same type two times).
 *
 * @param name what the test should be called in the output.
 * @param total the total amount of tests that have been run (adds to the value when done)
 * @param successful the total amount of tests that has been successful (adds to the value when done)
 */

template <typename T1_int, typename T1_string>
void container_test(string name, int& total, int& successful)
{

	container_test<T1_int, T1_string, T1_int, T1_string>(name, total, successful);
}

/** 
 * #### Method for running all tests. 
 * Will output the total number of tests and total number of successful tests.
 */
void test_concatenation()
{
	using IntVector = std::vector<int>;
	using StringVector = std::vector<string>;
	using IntDeque = std::deque<int>;
	using StringDeque = std::deque<string>;
	using IntArray = std::array<int, 7>;
	using StringArray = std::array<string, 5>;

	std::cout << "=== TEST CONCATENATION ===================" << endl;
	int total{0};
	int successful{0};
	container_test<IntVector, StringVector>("test_vector", total, successful);
	container_test<IntDeque, StringDeque>("test_deque", total, successful);
	container_test<IntArray, StringArray>("test_array", total, successful);

	container_test<IntVector, StringVector, IntDeque, StringDeque>("test_vector_deque", total, successful);
	container_test<IntVector, StringVector, IntArray, StringArray>("test_vector_array", total, successful);
	container_test<IntDeque, StringDeque, IntArray, StringArray>("test_deque_array", total, successful);

	cout << "|________________________________________|" << endl;
	string s = "|";
	string fill;
	fill.append(std::to_string(successful) + "/" + std::to_string(total));
	fill.append(" TESTS SUCCESSFUL");
	int fill_size = fill.size();
	int half = (40-fill_size)/2;
	string status = "|";
	status.append(half, ' ');
	status.append(fill);
	status.append(fill_size%2 == 0? half : (half+1), ' ');
	status.append("|\n");



	
	cout << status;
	std::cout << "==========================================" << endl;
}
int main()
{
	test_concatenation();
	return 0;
}