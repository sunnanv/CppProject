#include "concatenation.h"
#include <iostream>
#include <string>

#include <array>
#include <vector>
#include <deque>

#include <algorithm>


using std::cout;
using std::endl;

using std::string;

using std::array;
using std::vector;
using std::deque;

bool test_vector_int() 
{
	using IntVector = vector<int>;

	IntVector i1 = {1,2,3,4,5,6,7,8};
	IntVector i2 = {11,12,13,14,15};

	concatenation<IntVector, IntVector> conc(i1, i2);

	auto first5 = std::find(conc.begin(), conc.end(), 5);
	auto first14 = std::find(conc.begin(), conc.end(), 14);

	IntVector correct{5,6,7,8,11,12,13};
	IntVector result;
	std::copy(first5, first14, std::back_inserter(result));

	for(size_t i = 0; i != correct.size(); ++i)
	{
		//cout << result.at(i) << endl;
		if(correct.at(i) != result.at(i))
		{
			cout << "test_vector_int: FAILED! (copy) (" << correct.at(i) << " != " << result.at(i) << ")" << endl;
			return false;
		}
	}

	IntVector correct2{1,2,3,4,5,6,7,8,11,12,13,14,15};
	int i = 0;
	for(auto it = conc.begin(); it != conc.end(); ++it, ++i)
	{
		if(correct2.at(i) != *it)
		{
			cout << "test_vector_int: FAILED! (iter) (" << correct2.at(i) << " != " << *it << ")" << endl;
			return false;
		}
	}
	i = 0;
	for(auto it : conc)
	{
		if(correct2.at(i) != it)
		{
			cout << "test_vector_int: FAILED! (rangefor) (" << correct2.at(i) << " != " << it << ")" << endl;
			return false;
		}
		++i;
	}

	
	cout << "test_vector_int: PASSED" << endl;
	return true;
}

bool test_vector_string()
{
	using StringVector = vector<string>;

	StringVector s1 = {"this", "is", "a", "test"};
	StringVector s2 = {"for", "concatenation", "which", "will", "test", "string", "container"};

	concatenation<StringVector, StringVector> conc(s1, s2);

	auto firsta = std::find(conc.begin(), conc.end(), "a");
	auto firstwhich = std::find(conc.begin(), conc.end(), "which");

	vector<string> correct{"a", "test", "for", "concatenation"};

	std::vector<string> result;
	std::copy(firsta, firstwhich, std::back_inserter(result));

	for(size_t i = 0; i != correct.size(); ++i)
	{
		//cout << result.at(i) << endl;
		if(correct.at(i) != result.at(i))
		{
			cout << "test_vector_string: FAILED! (copy) (" << correct.at(i) << " != " << result.at(i) << ")" << endl;
			return false;
		}
	}


	StringVector correct2{"this", "is", "a", "test","for", "concatenation", "which", "will", "test", "string", "container"};
	int i = 0;
	for(auto it = conc.begin(); it != conc.end(); ++it, ++i)
	{
		//std::cout << correct2.at(i) << " = " << *it << endl;
		if(correct2.at(i) != *it)
		{
			cout << "test_vector_string: FAILED! (iter) (" << correct2.at(i) << " != " << *it << ")" << endl;
		}
	}

	i = 0;
	for(auto it : conc)
	{
		if(correct2.at(i) != it)
		{
			cout << "test_vector_string: FAILED! (rangefor) (" << correct2.at(i) << " != " << it << ")" << endl;
			return false;
		}
		++i;
	}
	cout << "test_vector_string: PASSED" << endl;
	return true;
}

bool test_deque_int() 
{
	using IntDeque = deque<int>;

	IntDeque i1 = {1,2,3,4,5,6,7,8};
	IntDeque i2 = {11,12,13,14,15};

	concatenation<IntDeque, IntDeque> conc(i1, i2);

	auto first5 = std::find(conc.begin(), conc.end(), 5);
	auto first14 = std::find(conc.begin(), conc.end(), 14);

	IntDeque correct{5,6,7,8,11,12,13};
	IntDeque result;
	std::copy(first5, first14, std::back_inserter(result));

	for(size_t i = 0; i != correct.size(); ++i)
	{
		//cout << result.at(i) << endl;
		if(correct.at(i) != result.at(i))
		{
			cout << "test_deque_int: FAILED! (copy) (" << correct.at(i) << " != " << result.at(i) << ")" << endl;
			return false;
		}
	}

	IntDeque correct2{1,2,3,4,5,6,7,8,11,12,13,14,15};
	int i = 0;
	for(auto it = conc.begin(); it != conc.end(); ++it, ++i)
	{
		if(correct2.at(i) != *it)
		{
			cout << "test_deque_int: FAILED! (iter) (" << correct2.at(i) << " != " << *it << ")" << endl;
		}
	}

	
	cout << "test_deque_int: PASSED" << endl;
	return true;
}

bool test_deque_string()
{
	using StringDeque = deque<string>;

	StringDeque s1 = {"this", "is", "a", "test"};
	StringDeque s2 = {"for", "concatenation", "which", "will", "test", "string", "container"};

	concatenation<StringDeque, StringDeque> conc(s1, s2);

	auto firsta = std::find(conc.begin(), conc.end(), "a");
	auto firstwhich = std::find(conc.begin(), conc.end(), "which");

	deque<string> correct{"a", "test", "for", "concatenation"};

	std::deque<string> result;
	std::copy(firsta, firstwhich, std::back_inserter(result));

	for(size_t i = 0; i != correct.size(); ++i)
	{
		//cout << result.at(i) << endl;
		if(correct.at(i) != result.at(i))
		{
			cout << "test_deque_string: FAILED! (copy) (" << correct.at(i) << " != " << result.at(i) << ")" << endl;
			return false;
		}
	}


	StringDeque correct2{"this", "is", "a", "test","for", "concatenation", "which", "will", "test", "string", "container"};
	int i = 0;
	for(auto it = conc.begin(); it != conc.end(); ++it, ++i)
	{
		//std::cout << correct2.at(i) << " = " << *it << endl;
		if(correct2.at(i) != *it)
		{
			cout << "test_deque_string: FAILED! (iter) (" << correct2.at(i) << " != " << *it << ")" << endl;
		}
	}

	i = 0;
	for(auto it : conc)
	{
		if(correct2.at(i) != it)
		{
			cout << "test_deque_int: FAILED! (rangefor) (" << correct2.at(i) << " != " << it << ")" << endl;
			return false;
		}
		++i;
	}

	cout << "test_deque_string: PASSED" << endl;
	return true;
}

bool test_deque_vector_int()
{
	using IntVector = vector<int>;
	using IntDeque = deque<int>;

	IntVector i_v = {1,2,3,4,5,6,7,8};
	IntDeque i_d = {34,35,36,37,38,39};

	concatenation<IntVector, IntDeque> conc(i_v, i_d);

	auto first4 = std::find(conc.begin(), conc.end(), 4);
	auto first38 = std::find(conc.begin(), conc.end(), 38);

	IntDeque correct = {4,5,6,7,8,34,35,36,37};
	IntDeque result;
	std::copy(first4, first38, std::back_inserter(result));

	for(size_t i = 0; i != correct.size(); ++i)
	{
		if(correct.at(i) != result.at(i))
		{
			cout << "test_deque_vector_int: FAILED! (copy) (" << correct.at(i) << " != " << result.at(i) << ")" << endl;
			return false;
		}
	}

	IntDeque correct2{1,2,3,4,5,6,7,8,34,35,36,37,38,39};
	int i = 0;
	for(auto it = conc.begin(); it != conc.end(); ++it, ++i)
	{
		if(correct2.at(i) != *it)
		{
			cout << "test_deque_vector_int: FAILED! (iter) (" << correct2.at(i) << " != " << *it << ")" << endl;
			return false;
		}
	}

	i = 0;
	for(auto it : conc)
	{
		if(correct2.at(i) != it)
		{
			cout << "test_deque_vector_int: FAILED! (rangefor) (" << correct2.at(i) << " != " << it << ")" << endl;
			return false;
		}
		++i;
	}
	

	cout << "test_deque_vector_int: PASSED" << endl;
	return true;
}

bool test_deque_vector_string()
{
	using StringVector = vector<string>;
	using StringDeque = deque<string>;

	StringVector s_v = {"hello", "I", "am", "testing", "concatenation"};
	StringDeque s_d = {"with", "vector", "and", "deque", "for", "type", "string"};

	concatenation<StringVector, StringDeque> conc(s_v, s_d);
	auto first_I = std::find(conc.begin(), conc.end(), "I");
	auto first_for = std::find(conc.begin(), conc.end(), "for");

	StringVector correct{"I", "am", "testing", "concatenation", "with", "vector", "and", "deque"};
	StringVector result;
	std::copy(first_I, first_for, back_inserter(result));

	for(size_t i = 0; i != correct.size(); ++i)
	{
		if(correct.at(i) != result.at(i))
		{
			cout << "test_deque_vector_string: FAILED! (copy) (" << correct.at(i) << " != " << result.at(i) << ")" << endl;
			return false;
		}
	}

	StringVector correct2{"hello", "I", "am", "testing", "concatenation", "with", "vector", "and", "deque", "for", "type", "string"};
	int i = 0;
	for(auto it = conc.begin(); it != conc.end(); ++it, ++i)
	{
		if(correct2.at(i) != *it)
		{
			cout << "test_deque_vector_string: FAILED! (iter) (" << correct2.at(i) << " != " << *it << ")" << endl;
			return false;
		}
	}

	i = 0;
	for(auto it : conc)
	{
		if(correct2.at(i) != it)
		{
			cout << "test_deque_vector_string: FAILED! (rangefor) (" << correct2.at(i) << " != " << it << ")" << endl;
			return false;
		}
		++i;
	}
	

	cout << "test_deque_vector_string: PASSED" << endl;
	return true;
}



int main()
{
	std::cout << "=== TEST CONCATENATION ===================" << endl;
	bool a = test_vector_int();
	bool b = test_vector_string();
	bool c = test_deque_int();
	bool d = test_deque_string();
	bool e = test_deque_vector_int();
	bool f = test_deque_vector_string();
	if(a && b && c && d && e && f) 
	{
		cout << " ________________________________________ " << endl;
		cout << "|            ALL TESTS PASSED            |" << endl;
	}
	std::cout << "==========================================" << endl;
	return 0;
}