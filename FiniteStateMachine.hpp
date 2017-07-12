#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "Transition.hpp"

using namespace std;

template <typename StateType, typename TransitionType>
class FiniteStateMachine {
	using Transition_ = Transition<StateType, TransitionType>;
	using Transitions_ = vector<Transition_>;

	vector<const shared_ptr<StateType>> States; //List of all states the FSM has
	Transitions_ Transitions; //List of all transitions the FSM has
	shared_ptr<StateType> StartState; //Starting state of the FSM

	//Used during the Consume process:
	Transitions_ SingleItemTransitions;
	Transitions_ MultipleItemTransitions;


	void GroupElementsByMultiTransitions() { 
		SingleItemTransitions.clear();
		MultipleItemTransitions.clear();
	
		for (int i = 0; i < Transitions.size(); i++) {
			if (Transitions[i].MultipleInputsRequired())
				MultipleItemTransitions.push_back(Transitions[i]);
			else
				SingleItemTransitions.push_back(Transitions[i]);
		}
	}

public:
	
	void AddState(const shared_ptr<StateType> state);

	void SpecifyStartState(shared_ptr<StateType> start);

	void DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const TransitionType& transition);

	void DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, TransitionType&& transition);

	void DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const vector<shared_ptr<TransitionType>>& transitions) {
		//Check for existence of from state
		if (find(States.begin(), States.end(), from) == States.end())
			cerr << "ERROR: STATE " << *from << " DOES NOT EXIST" << endl;

		//Check for existence of to state
		if (find(States.begin(), States.end(), to) == States.end())
			cerr << "ERROR: STATE " << *to << " DOES NOT EXIST" << endl;

		Transitions.push_back(Transition_(from, to, transitions));
	}


	void DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const vector<TransitionType>& transitions) {
		
		auto ptrVec = vector<shared_ptr<TransitionType>>();
		for (int i = 0; i < transitions.size(); i++) {
			ptrVec.push_back(shared_ptr<TransitionType>(new TransitionType(transitions[i])));
		}

		DefineTransition(from, to, ptrVec);
	}

	shared_ptr<Transition_> FindTransition(const shared_ptr<StateType> currentState, const vector<TransitionType>& data, int& currentIndex, vector<shared_ptr<TransitionType>>& consumed) const;

	Transitions_ Consume(const vector<TransitionType>& data, bool ignoreWhitespace = true, bool verbose = false);
};

#include "FiniteStateMachine.tpp"