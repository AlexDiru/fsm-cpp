#include <iostream>
#include <vector>
#include <algorithm>

#include "StringFiniteStateMachine.hpp"

using namespace std;

static string ToStringBool(bool& a) {
		if (a)
			return "1";
		return "0";
	}

	static string ToStringChar(char& a) {
		stringstream ss;
		string s;
		ss << a;
		ss >> s;
		return s;
	}

void DemonstrateFiniteStateMachine() {

	cout << "***Boolean FSM***" << endl;

	auto *FSM = new FiniteStateMachine<string, bool>();

	shared_ptr<string> STATE_THREE (new string ("THREE"));
	shared_ptr<string> STATE_FOUR (new string("FOUR"));

	FSM->AddState(STATE_THREE);
	FSM->AddState(STATE_FOUR);

	FSM->SpecifyStartState(STATE_THREE);

	FSM->DefineTransition(STATE_THREE, STATE_FOUR, vector<bool>{true,false,false});
	FSM->DefineTransition(STATE_THREE, STATE_THREE, vector<bool>{true,true});

	vector<bool> input{true, true, true, false, false};

	cout << "Input: ";
	for (int i = 0; i < input.size(); i++) {
		cout << (input[i] ? "1" : "0");
	}
	cout << endl;

	auto transitions = FSM->Consume(input);

	cout << "FSM Output:" << endl;

	for (int i = 0; i < transitions.size(); i++) 
		cout << transitions[i].ToString([](bool b) -> string { return b ? "1" : "0"; }) << endl;

	delete FSM;

	cout << endl;
}

void DemonstrateStringFiniteStateMachine() {
	cout << "***String FSM***" << endl;

	auto *FSM = new StringFiniteStateMachine();


	shared_ptr<string> STATE_START (new string{"START"});
	shared_ptr<string> STATE_NUMBER (new string{"NUMBER"});
	shared_ptr<string> STATE_ID (new string{"IDENTIFIER"});
	shared_ptr<string> STATE_OPERATOR (new string{"OPERATOR"});

	FSM->AddState(STATE_START);
	FSM->AddState(STATE_NUMBER);
	FSM->AddState(STATE_ID);
	FSM->AddState(STATE_OPERATOR);

	FSM->SpecifyStartState(STATE_START);

	const string operators = "+-/*=";

	FSM->DefineTransitions(STATE_START,STATE_NUMBER,StringFiniteStateMachine::ZERO_TO_NINE,STATE_START);
	FSM->DefineTransitions(STATE_START,STATE_ID,StringFiniteStateMachine::A_TO_z,STATE_START);
	FSM->DefineTransitions(STATE_START,STATE_OPERATOR, operators,STATE_START);

	string input = "12x + ab = -2a";

	cout << "Input: " << input << endl;

	vector<char> data = StringFiniteStateMachine::StringToVectorChar(input);

	auto transitions = FSM->Consume(data);

	cout << "FSM Output:" << endl;

	for (int i = 0; i < transitions.size(); i++) 
		cout << transitions[i].ToString([](char a) {
			stringstream ss;
			string s;
			ss << a;
			ss >> s;
			return s;
		}) << endl;
	
	delete FSM;
}

int main() {

	DemonstrateFiniteStateMachine();
	DemonstrateStringFiniteStateMachine();

	return 0;
}