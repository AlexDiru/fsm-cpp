#include <iostream>
#include <vector>
#include <algorithm>

#include "StringFiniteStateMachine.hpp"

using namespace std;



void DemonstrateStringFiniteStateMachine() {
	auto *FSM = new StringFiniteStateMachine();

	shared_ptr<string> STATE_NUMBER (new string("NUMBER"));

	shared_ptr<string> STATE_ID (new string("IDENTIFIER"));

	shared_ptr<string> STATE_OPERATOR (new string("OPERATOR"));

	FSM->AddState(STATE_NUMBER);
	FSM->AddState(STATE_ID);
	FSM->AddState(STATE_OPERATOR);

	FSM->SpecifyStartState(STATE_NUMBER);

	const string operators = "+-/*=";

	FSM->DefineTransitions(STATE_NUMBER,STATE_NUMBER,StringFiniteStateMachine::ZERO_TO_NINE);
	FSM->DefineTransitions(STATE_NUMBER,STATE_ID,StringFiniteStateMachine::A_TO_z);
	FSM->DefineTransitions(STATE_NUMBER,STATE_OPERATOR, operators);
	FSM->DefineTransitions(STATE_ID, STATE_ID, StringFiniteStateMachine::A_TO_z);
	FSM->DefineTransitions(STATE_ID, STATE_NUMBER, StringFiniteStateMachine::ZERO_TO_NINE);
	FSM->DefineTransitions(STATE_ID, STATE_OPERATOR, operators);
	FSM->DefineTransitions(STATE_OPERATOR, STATE_NUMBER, StringFiniteStateMachine::ZERO_TO_NINE);
	FSM->DefineTransitions(STATE_OPERATOR, STATE_ID, StringFiniteStateMachine::A_TO_z);
	//Can't have two operators next to each other except =- e.g. 12x = -3y
	FSM->DefineTransitions(STATE_OPERATOR, STATE_OPERATOR, "-");


	string input = "12x + ab = -2a";

	cout << "Input: " << input << endl;

	vector<char> data = StringFiniteStateMachine::StringToVectorChar(input);

	auto transitions = FSM->Consume(data);

	cout << "Total Number of Transitions: " << transitions.size() << endl;
}

int main() {

	DemonstrateStringFiniteStateMachine();

	return 0;
}