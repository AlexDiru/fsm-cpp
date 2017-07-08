#include <iostream>
#include <vector>
#include <algorithm>

#include "StringFiniteStateMachine.hpp"

using namespace std;





void DemonstrateFiniteStateMachine() {
	auto *FSM = new FiniteStateMachine<string, char>();

	string *s1 = new string();
	*s1 = "Start";

	string *s2 = new string();
	*s2 = "NUMBER";

	string *s3 = new string();
	*s3 = "IDENTIFIER";

	FSM->AddState(s1);
	FSM->AddState(s2);
	FSM->SpecifyStartState(s1);

	FSM->DefineTransition(s1,s2,'0');
	FSM->DefineTransition(s1,s2,'1');
	FSM->DefineTransition(s1,s2,'2');
	FSM->DefineTransition(s1,s2,'3');
	FSM->DefineTransition(s1,s2,'4');
	FSM->DefineTransition(s1,s2,'5');
	FSM->DefineTransition(s1,s2,'6');
	FSM->DefineTransition(s1,s2,'7');
	FSM->DefineTransition(s1,s2,'8');
	FSM->DefineTransition(s1,s2,'9');

	FSM->DefineTransition(s2,s2,'0');
	FSM->DefineTransition(s2,s2,'1');
	FSM->DefineTransition(s2,s2,'2');
	FSM->DefineTransition(s2,s2,'3');
	FSM->DefineTransition(s2,s2,'4');
	FSM->DefineTransition(s2,s2,'5');
	FSM->DefineTransition(s2,s2,'6');
	FSM->DefineTransition(s2,s2,'7');
	FSM->DefineTransition(s2,s2,'8');
	FSM->DefineTransition(s2,s2,'9');

	FSM->DefineTransition(s1, s3, 'x');
	FSM->DefineTransition(s2, s3, 'x');


	FSM->DefineTransition(s3,s2,'0');
	FSM->DefineTransition(s3,s2,'1');
	FSM->DefineTransition(s3,s2,'2');
	FSM->DefineTransition(s3,s2,'3');
	FSM->DefineTransition(s3,s2,'4');
	FSM->DefineTransition(s3,s2,'5');
	FSM->DefineTransition(s3,s2,'6');
	FSM->DefineTransition(s3,s2,'7');
	FSM->DefineTransition(s3,s2,'8');
	FSM->DefineTransition(s3,s2,'9');

	FSM->DefineTransition(s2,s1,'e');

	string input = "123x12";

	cout << "Input: " << input << endl;

	vector<char> data = StringFiniteStateMachine::StringToVectorChar("123x12");

	FSM->Consume(data);
}

void DemonstrateStringFiniteStateMachine() {
	auto *FSM = new StringFiniteStateMachine();

	string *STATE_NUMBER = new string();
	*STATE_NUMBER = "NUMBER";

	string *STATE_ID = new string();
	*STATE_ID = "IDENTIFIER";

	string *STATE_OPERATOR = new string();
	*STATE_OPERATOR = "OPERATOR";

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