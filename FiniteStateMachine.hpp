#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "Transition.hpp"

using namespace std;



template <typename StateType, typename TransitionType>
class FiniteStateMachine {

	using TTransition = Transition<StateType, TransitionType>;
	using TTransitions = vector<TTransition>;

	vector<const shared_ptr<StateType>> States; //List of all states the FSM has
	TTransitions Transitions; //List of all transitions the FSM has
	shared_ptr<StateType> StartState; //Starting state of the FSM

	//Used during the Consume process:
	TTransitions SingleItemTransitions;
	TTransitions MultipleItemTransitions;


	shared_ptr<TTransition> FindTransition(const shared_ptr<StateType> currentState, const vector<TransitionType>& data, int& currentIndex, vector<shared_ptr<TransitionType>>& consumed) const;

	static vector<shared_ptr<TransitionType>> VectorToVectorOfPointers(const vector<TransitionType>& vec) {
		vector<shared_ptr<TransitionType>> vecPtr;
		for (int i = 0; i < vec.size(); i++)
			vecPtr.push_back(shared_ptr<TransitionType>(new TransitionType(vec[i])));
		return vecPtr;
	}
public:
	
	void AddState(const shared_ptr<StateType> state);

	void SpecifyStartState(shared_ptr<StateType> start);

	void DefineTransition(const TTransition& transition) {
		//Check for existence of from state
		if (find(States.begin(), States.end(), transition.GetFromState()) == States.end())
			cerr << "ERROR: STATE " << *(transition.GetFromState()) << " DOES NOT EXIST" << endl;

		//Check for existence of to state
		if (find(States.begin(), States.end(), transition.GetToState()) == States.end())
			cerr << "ERROR: STATE " << *(transition.GetToState()) << " DOES NOT EXIST" << endl;

		Transitions.push_back(transition);
	}

	void DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const TransitionType& transition);
	void DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, TransitionType&& transition);
	void DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const vector<shared_ptr<TransitionType>>& transitions);
	void DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const vector<TransitionType>& transitions);

	void DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const TransitionType& transition, const shared_ptr<StateType> teleport) {
		//Check for existence of from state
		if (find(States.begin(), States.end(), from) == States.end())
			cerr << "ERROR: STATE " << *from << " DOES NOT EXIST" << endl;

		//Check for existence of to state
		if (find(States.begin(), States.end(), to) == States.end())
			cerr << "ERROR: STATE " << *to << " DOES NOT EXIST" << endl;

		if (teleport != nullptr) 
			if (find(States.begin(), States.end(), teleport) == States.end())
				cerr << "ERROR: STATE " << *teleport << " DOES NOT EXIST" << endl;

		Transitions.push_back(TTransition(from, to, shared_ptr<TransitionType>(new TransitionType(transition)), teleport));
	}


	void DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const vector<TransitionType>& transitions, const shared_ptr<StateType> teleport) {
		DefineTransition(from, to, FiniteStateMachine::VectorToVectorOfPointers(transitions), teleport);
	}



	void DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const vector<shared_ptr<TransitionType>>& transitions, const shared_ptr<StateType> teleport) {
		//Check for existence of from state
		if (find(States.begin(), States.end(), from) == States.end())
			cerr << "ERROR: STATE " << *from << " DOES NOT EXIST" << endl;

		//Check for existence of to state
		if (find(States.begin(), States.end(), to) == States.end())
			cerr << "ERROR: STATE " << *to << " DOES NOT EXIST" << endl;

		if (teleport != nullptr) 
			if (find(States.begin(), States.end(), teleport) == States.end())
				cerr << "ERROR: STATE " << *teleport << " DOES NOT EXIST" << endl;

		Transitions.push_back(TTransition(from, to, transitions, teleport));
	}

	TTransitions Consume(const vector<TransitionType>& data, bool ignoreWhitespace = true, bool verbose = false);
};

#include "FiniteStateMachine.tpp"