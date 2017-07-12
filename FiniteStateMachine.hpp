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


	void SortTransitionsByLength();

public:
	
	void AddState(const shared_ptr<StateType> state);

	void SpecifyStartState(shared_ptr<StateType> start);

	void DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const TransitionType& transition);
	void DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, TransitionType&& transition);
	void DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const vector<shared_ptr<TransitionType>>& transitions);
	void DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const vector<TransitionType>& transitions);

	shared_ptr<Transition_> FindTransition(const shared_ptr<StateType> currentState, const vector<TransitionType>& data, int& currentIndex, vector<shared_ptr<TransitionType>>& consumed) const;

	Transitions_ Consume(const vector<TransitionType>& data, bool ignoreWhitespace = true, bool verbose = false);
};

#include "FiniteStateMachine.tpp"