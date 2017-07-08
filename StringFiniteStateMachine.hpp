#pragma once

#include <vector>

#include "FiniteStateMachine.hpp"

using namespace std;

//This class has methods to better handle strings
class StringFiniteStateMachine : public FiniteStateMachine<string, char> {
public:

	static const string A_TO_Z;
	static const string A_TO_z;
	static const string a_TO_z;
	static const string ZERO_TO_NINE;

	static vector<char> StringToVectorChar(const string& str);

	void DefineTransitions(shared_ptr<string> from, shared_ptr<string> to, const string& transitions);

	void DefineTransitions(shared_ptr<string> from, shared_ptr<string> to, string&& transitions);
};