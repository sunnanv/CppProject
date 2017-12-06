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

using std::array;
using std::vector;
using std::deque;
void printCell(string name, bool passed, string why) 
{
	std::stringstream ss;
	/* Create first row */
	ss << "|  " << name << ":";
	int rowi = 0;
	if(passed)
	{
		ss << " PASSED";
	} else 
	{
		ss << " FAILED";
	}

	/* fill with blankspace */
	rowi = ss.str().size()-3;
	while(rowi != 38)
	{
		ss.put(' ');
		++rowi;
	}
	ss << "|\n|";

	/* If not passed, output why */
	rowi = 0;
	if(!passed)
	{
		ss << "    ";
		for(size_t i = 0; i != why.size(); ++i)
		{
			if(i != 0 && i % 33 == 0)
			{
				ss << "   |\n|    ";
				rowi = 0;
			}
			++rowi;
			ss.put(why.at(i));
		}
		while(rowi != 36)
		{
			ss.put(' ');
			++rowi;
		}
		ss << "|\n|";
	}

	/* Ending line */
	for(int i = 0; i != 40; ++i)
	{
		ss.put('-');
	}
	ss << "|\n";

	std::cout << ss.str();
}

/* Template method for testing std::copy, iterator and rangefor */
template<typename T1, typename T2>
bool test(string name, T1& first, T2& second, typename T1::value_type find[])
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
		//cout << result.at(i) << endl;
		if(correct_part.at(i1) != result.at(i1))
		{
			string a, b;
			std::ostringstream ss1;
			std::ostringstream ss2;
			ss1 << result.at(i1);
			ss2 << correct_part.at(i1);
			a = ss1.str();
			b = ss2.str();
			why = "(copy " + std::to_string(i1)  + ") (" + a + " != " + b + ")";
			success = false;
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
			    string a, b;
			    std::ostringstream ss1;
				std::ostringstream ss2;
				ss1 << *it;
				ss2 << correct_full.at(i2);
				a = ss1.str();
				b = ss2.str();

				why = "(iter " + std::to_string(i2) + ") (" + a + " != " + b + ")";
				success = false;
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
				string a, b;
				std::ostringstream ss1;
				std::ostringstream ss2;
				ss1 << it;
				ss2 << correct_full.at(i2);
				a = ss1.str();
				b = ss2.str();

				why = "(rangefor " + std::to_string(i3) + ") (" + a + " != " + b + ")";
				success = false;
			}
			++i3;
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

	
	printCell(name, success, why);
	return success;
}

template<typename T1, typename T2>
bool test_write_int(string name, T1 first, T2 second)
{
	bool success = true;
	string why = "";
	concatenation<T1, T2> conc(first, second);

	std::iota(conc.begin(), conc.end(), 0);
	int i1 = 0;
	for(auto it = conc.begin(); it != conc.end(); ++it)
	{
		if(*it != i1)
		{
			why = "(iota pos " + std::to_string(i1) + ") (wrong value, was " + std::to_string(*it) + ")";
			success = false;
		}
		++i1;
	}

	if(success)
	{
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
			}
			++i2;
		}
	}

	printCell(name, success, why);
	return success;
}

void test_concatenation()
{
	std::cout << "=== TEST CONCATENATION ===================" << endl;
	using IntVector = vector<int>;
	using StringVector = vector<string>;
	using IntDeque = deque<int>;
	using StringDeque = deque<string>;
	using IntArray = array<int, 7>;
	using StringArray = array<string, 5>;

	IntVector i_v1 = {1,2,3,4,5,6,7};
	IntVector i_v2 = {10,11,12,13,14};
	StringVector s_v1 = {"this", "is", "a", "test", "for"};
	StringVector s_v2 = {"concatenation", "on", "string", "container"};

	IntDeque i_d1 = {1,2,3,4,5,6,7};
	IntDeque i_d2 = {10,11,12,13,14};
	StringDeque s_d1 = {"this", "is", "a", "test", "for"};
	StringDeque s_d2 = {"concatenation", "on", "string", "container"};
	IntDeque find = {5,12};

	IntArray i_a1 = {1,2,3,4,5,6,7};
	IntArray i_a2 = {10,11,12,13,14};
	StringArray s_a1 = {"this", "is", "a", "test", "for"};
	StringArray s_a2 = {"concatenation", "on", "string", "container", "array"};

	int i_find[2] = {5, 13};
	string s_find[2] = {"a", "on"};

	bool a = test<IntVector, IntVector>("test_vector_int", i_v1, i_v2, i_find);
	bool b = test<StringVector, StringVector>("test_vector_string", s_v1, s_v2, s_find);
	bool c = test<IntDeque, IntDeque>("test_deque_int", i_d1, i_d2, i_find);
	bool d = test<StringDeque, StringDeque>("test_deque_string", s_d1, s_d2, s_find);
	bool e = test<IntArray, IntArray>("test_array_int", i_a1, i_a2, i_find);
	bool f = test<StringArray, StringArray>("test_array_string", s_a1, s_a2, s_find);
	bool g = test<IntVector, IntDeque>("test_vector_deque_int", i_v1, i_d2, i_find);
	bool h = test<StringVector, StringDeque>("test_vector_deque_string", s_v1, s_d2, s_find);
	bool i = test<IntVector, IntArray>("test_vector_array_int", i_v1, i_a2, i_find);
	bool j = test<StringVector, StringArray>("test_vector_array_string", s_v1, s_a2, s_find);
	bool k = test<IntDeque, IntArray>("test_deque_array_int", i_d1, i_a2, i_find);
	bool l = test<StringDeque, StringArray>("test_deque_array_string", s_d1, s_a2, s_find);

	bool m = test_write_int<IntVector, IntVector>("test_write_vector_int", i_v1, i_v2);
	bool n = test_write_int<IntDeque, IntDeque>("test_write_deque_int", i_d1, i_d2);
	bool o = test_write_int<IntArray, IntArray>("test_write_array_int", i_a1, i_a2);
	bool p = test_write_int<IntVector, IntDeque>("test_write_vector_deque_int", i_v1, i_d2);
	bool q = test_write_int<IntVector, IntArray>("test_write_vector_array_int", i_v1, i_a2);
	if(a && b && c && d && e && f && g && h && i && j && k && l && m && n && o && p && q)
	{
		cout << "|________________________________________|" << endl;
		cout << "|            ALL TESTS PASSED            |" << endl;
	}
	std::cout << "==========================================" << endl;
}
int main()
{
	test_concatenation();
	return 0;
}