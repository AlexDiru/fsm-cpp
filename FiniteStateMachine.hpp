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

	vector<const StateType*> States; //List of all states the FSM has
	Transitions_ Transitions; //List of all transitions the FSM has
	StateType *StartState; //Starting state of the FSM

public:
	void AddState(const StateType* state);

	void SpecifyStartState(StateType* start);

	void DefineTransition(const StateType* from, const StateType* to, const TransitionType& transition);

	void DefineTransition(const StateType* from, const StateType* to, const TransitionType&& transition);

	const Transition_* FindTransition(const StateType* currentState, const TransitionType& currentData) const;

	Transitions_ Consume(const vector<TransitionType>& data, bool ignoreWhitespace = true, bool verbose = true) const;
};

#include "FiniteStateMachine.tpp"