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
void printCell(string name, bool passed, string why) 
{
	string o = "|  ";
	o += name + ":";
	int rowi = 0;
	if(passed)
	{
		o += " PASSED";
	} else 
	{
		o += " FAILED";
	}

	rowi = o.size()-3;
	while(rowi != 38)
	{
		o += " ";
		++rowi;
	}
	o += "|\n|";

	rowi = 0;
	if(!passed)
	{
		o += "    ";
		for(size_t i = 0; i != why.size(); ++i)
		{
			if(i != 0 && i % 33 == 0)
			{
				o += "   |\n|  ";
				rowi = 0;
			}
			++rowi;
			o += why.at(i);
		}
		while(rowi != 36)
		{
			o += " ";
			++rowi;
		}
		o += "|\n|";
	}
	

	


	
	for(int i = 0; i != 40; ++i)
	{
		o += "-";
	}
	o += "|\n";
	std::cout << o;

}

bool test_vector_int() 
{
	string name = "test_vector_int";
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
			string s = "(copy " + std::to_string(i)  + ") (" + std::to_string(correct.at(i)) + " != " + std::to_string(result.at(i)) + ")";
			printCell(name, false, s);
			return false;
		}
	}

	IntVector correct2{1,2,3,4,5,6,7,8,11,12,13,14,15};
	int i = 0;
	for(auto it = conc.begin(); it != conc.end(); ++it, ++i)
	{
		if(correct2.at(i) != *it)
		{
			string s = "(iter " + std::to_string(i) + ") (" + std::to_string(correct2.at(i)) + " != " + std::to_string(*it) + ")";
			printCell(name, false, s);
			return false;
		}
	}
	i = 0;
	for(auto it : conc)
	{
		if(correct2.at(i) != it)
		{
			string s = "(rangefor " + std::to_string(i) + ") (" + std::to_string(correct2.at(i)) + " != " + std::to_string(it) + ")";
			printCell(name, false, s);
			return false;
		}
		++i;
	}

	
	printCell(name, true, "");
	return true;
}

bool test_vector_string()
{
	string name = "test_vector_string";
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
			string s = "(copy " + std::to_string(i) + ") (" + correct.at(i) + " != " + result.at(i) + ")";
			printCell(name, false, s);
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
			string s = "(iter " + std::to_string(i) + ") (" + correct2.at(i) + " != " + *it + ")";
			printCell(name, false, s);
			return false;
		}
	}

	i = 0;
	for(auto it : conc)
	{
		if(correct2.at(i) != it)
		{
			string s = "(rangefor " + std::to_string(i) + ") (" + correct2.at(i) + " != " + it + ")";
			printCell(name, false, s);
			return false;
		}
		++i;
	}
	printCell(name, true, "");
	return true;
}

bool test_deque_int() 
{
	string name = "test_deque_int";
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
			string s ="(copy " + std::to_string(i) + ") (" + std::to_string(correct.at(i)) + " != " + std::to_string(result.at(i)) + ")";
			printCell(name, false, s);
			return false;
		}
	}

	IntDeque correct2{1,2,3,4,5,6,7,8,11,12,13,14,15};
	int i = 0;
	for(auto it = conc.begin(); it != conc.end(); ++it, ++i)
	{
		if(correct2.at(i) != *it)
		{
			string s = "(iter " + std::to_string(i) + ") (" + std::to_string(correct2.at(i)) + " != " + std::to_string(*it) + ")";
			printCell(name, false, s);
			return false;
		}
	}

	
	printCell(name, true, "");
	return true;
}

bool test_deque_string()
{
	string name = "test_deque_string";
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
			string s = "(copy " + std::to_string(i) + ") (" + correct.at(i) + " != " + result.at(i) + ")";
			printCell(name, false, s);
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
			string s = "(iter " + std::to_string(i) + ") (" + correct2.at(i) + " != " + *it + ")";
			printCell(name, false, s);
			return false;
		}
	}

	i = 0;
	for(auto it : conc)
	{
		if(correct2.at(i) != it)
		{
			string s = "(rangefor " + std::to_string(i) + ") (" + correct2.at(i) + " != " + it + ")";
			printCell(name, false, s);
			return false;
		}
		++i;
	}

	printCell(name, true, "");
	return true;
}

bool test_deque_vector_int()
{
	string name = "test_deque_vector_int";
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
			string s = "(copy " + std::to_string(i) + ") (" + std::to_string(correct.at(i)) + " != " + std::to_string(result.at(i)) + ")";
			printCell(name, false, s);
			return false;
		}
	}

	IntDeque correct2{1,2,3,4,5,6,7,8,34,35,36,37,38,39};
	int i = 0;
	for(auto it = conc.begin(); it != conc.end(); ++it, ++i)
	{
		if(correct2.at(i) != *it)
		{
			string s = "(iter " + std::to_string(i) + ") (" + std::to_string(correct2.at(i)) + " != " + std::to_string(*it) + ")";
			printCell(name, false, s);
			return false;
		}
	}

	i = 0;
	for(auto it : conc)
	{
		if(correct2.at(i) != it)
		{
			string s = "(rangefor " + std::to_string(i) + ") (" + std::to_string(correct2.at(i)) + " != " + std::to_string(it) + ")";
			printCell(name, false, s);
			return false;
		}
		++i;
	}
	

	printCell(name, true, "");
	return true;
}

bool test_deque_vector_string()
{
	string name = "test_deque_vector_string";
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
			string s = "(copy) (" + correct.at(i) + " != " + result.at(i) + ")";
			printCell(name, false, s);
			return false;
		}
	}

	StringVector correct2{"hello", "I", "am", "testing", "concatenation", "with", "vector", "and", "deque", "for", "type", "string"};
	int i = 0;
	for(auto it = conc.begin(); it != conc.end(); ++it, ++i)
	{
		if(correct2.at(i) != *it)
		{
			string s = "(iter " + std::to_string(i) + ") (" + correct2.at(i) + " != " + *it + ")";
			printCell(name, false, s);
			return false;
		}
	}

	i = 0;
	for(auto it : conc)
	{
		if(correct2.at(i) != it)
		{
			string s = "(rangefor " + std::to_string(i) + ") (" + correct2.at(i) + " != " + it + ")";
			printCell(name, false, s);
			return false;
		}
		++i;
	}
	

	printCell(name, true, "");
	return true;
}

bool test_array_int()
{
	string name = "test_array_int";
	using IntArray = array<int, 8>;

	IntArray a1 = {1,2,3,4,5,6,7,8};
	IntArray a2 = {9,10,11,12,13,14,15,16};

	concatenation<IntArray, IntArray> conc(a1, a2);

	auto first6 = std::find(conc.begin(), conc.end(), 6);
	auto first13 = std::find(conc.begin(), conc.end(), 13);

	vector<int> correct{6,7,8,9,10,11,12};
	vector<int> result;
	std::copy(first6, first13, back_inserter(result));
	for(size_t i = 0; i != correct.size(); ++i)
	{
		if(correct.at(i) != result.at(i))
		{
			string s = "(copy " + std::to_string(i) + ") (" + std::to_string(correct.at(i)) + " != " + std::to_string(result.at(i)) + ")";
			printCell(name, false, s);
			return false;
		}
	} 
	int i = 0;
	vector<int> correct2{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	for(auto it = conc.begin(); it != conc.end(); ++it)
	{
		if(correct2.at(i) != *it) 
		{
			string s ="(iter " + std::to_string(i) + ") (" + std::to_string(correct.at(i)) + " != " + std::to_string(*it) + ")";
			printCell(name, false, s);
			return false;
		}
		++i;
	}
	i = 0;
	for(auto it : conc)
	{
		if(correct2.at(i) != it)
		{
			string s = "(rangefor " + std::to_string(i) + ") (" + std::to_string(correct.at(i)) + " != " + std::to_string(it) + ")";
			printCell(name, false, s);
			return false;
		}
		++i;
	}


	printCell(name, true, "");
	return true;
}

bool test_array_string()
{
	string name = "test_array_string";
	using StringArray = array<string, 5>;

	StringArray a1 = {"hello", "I", "am", "testing", "concatenation"};
	StringArray a2 = {"with", "array", "for", "type", "string"};

	concatenation<StringArray, StringArray> conc(a1, a2);

	auto first_testing = std::find(conc.begin(), conc.end(), "testing");
	auto first_for = std::find(conc.begin(), conc.end(), "for");

	vector<string> correct{"testing", "concatenation", "with", "array"};
	vector<string> result;
	std::copy(first_testing, first_for, back_inserter(result));
	for(size_t i = 0; i != correct.size(); ++i)
	{
		if(correct.at(i) != result.at(i))
		{
			string s = "(copy " + std::to_string(i) + ") (" + correct.at(i) + " != " + result.at(i) + ")";
			printCell(name, false, s);
			return false;
		}
	} 
	int i = 0;
	vector<string> correct2{"hello", "I", "am", "testing", "concatenation", "with", "array", "for", "type", "string"};
	for(auto it = conc.begin(); it != conc.end(); ++it)
	{
		if(correct2.at(i) != *it) 
		{
			string s = "(iter " + std::to_string(i) + ") (" + correct.at(i) + " != " + *it + ")";
			printCell(name, false, s);
			return false;
		}
		++i;
	}
	i = 0;
	for(auto it : conc)
	{
		if(correct2.at(i) != it)
		{
			string s = "(rangefor " + std::to_string(i) + ") (" + correct.at(i) + " != " + it + ")";
			printCell(name, false, s);
			return false;
		}
		++i;
	}


	printCell(name, true, "");
	return true;
}

bool test_array_vector_int()
{

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
	bool g = test_array_int();
	bool h = test_array_string();
	if(a && b && c && d && e && f && g && h) 
	{
		cout << "|________________________________________|" << endl;
		cout << "|            ALL TESTS PASSED            |" << endl;
	}
	std::cout << "==========================================" << endl;
	return 0;
}