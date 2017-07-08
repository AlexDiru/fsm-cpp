#include "StringFiniteStateMachine.hpp"

const string StringFiniteStateMachine::A_TO_Z = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string StringFiniteStateMachine::A_TO_z = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const string StringFiniteStateMachine::a_TO_z = "abcdefghijklmnopqrstuvwxyz";
const string StringFiniteStateMachine::ZERO_TO_NINE = "0123456789";

vector<char> StringFiniteStateMachine::StringToVectorChar(const string& str) {
	vector<char> v;
	for (int i = 0; i < str.length(); i++)
		v.push_back(str[i]);
	return v;
}

void StringFiniteStateMachine::DefineTransitions(string* from, string* to, const string& transitions) {
	for (int i = 0; i < transitions.length();i++) {
		DefineTransition(from, to, transitions[i]);
	}
}

void StringFiniteStateMachine::DefineTransitions(string* from, string* to, string&& transitions) {
	for (int i = 0; i < transitions.length();i++) {
		DefineTransition(from, to, transitions[i]);
	}
}