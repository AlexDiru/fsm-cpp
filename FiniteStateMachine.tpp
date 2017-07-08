#pragma once

template <typename StateType, typename TransitionType>
vector<Transition<StateType, TransitionType>> FiniteStateMachine<StateType, TransitionType>::Consume(const vector<TransitionType>& data, bool ignoreWhitespace, bool verbose) const {
	
	StateType const* currentState = StartState;
	StateType const* previousState = nullptr;
	Transitions_ stateChanges;

	for (int i = 0; i < data.size(); i++) {

		if (ignoreWhitespace && data[i] == ' ')
			continue;

		if (verbose) {
			cout << "Current State: " << *currentState << endl;
			cout << "Consuming: " << data[i] << endl;
		}

		auto transition = FindTransition(currentState, data[i]);

		if (transition == nullptr) {
			cerr << "ERROR: TRANSITION NOT FOUND INVALID INPUT" << endl;
		} else {
			previousState = currentState;
			currentState = transition->GetEndState();
			stateChanges.push_back(Transition_(currentState, previousState, &data[i]));
		}

	}

	if (verbose)
		cout << "Final State: " << *currentState << endl;

	return stateChanges;
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::AddState(const StateType* state) {
	States.push_back(state);
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::SpecifyStartState(StateType* start) {
	StartState = start;
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::DefineTransition(const StateType* from, const StateType* to, const TransitionType& transition) {
	//Check for existence of from state
	if (find(States.begin(), States.end(), from) == States.end())
		cerr << "ERROR: STATE " << *from << " DOES NOT EXIST" << endl;

	//Check for existence of to state
	if (find(States.begin(), States.end(), to) == States.end())
		cerr << "ERROR: STATE " << *to << " DOES NOT EXIST" << endl;

	Transitions.push_back(Transition_(from, to, &transition));
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::DefineTransition(const StateType* from, const StateType* to, const TransitionType&& transition) {
	TransitionType temp = transition;
	DefineTransition(from, to, transition);
}

template <typename StateType, typename TransitionType>
const Transition<StateType, TransitionType>* FiniteStateMachine<StateType, TransitionType>::FindTransition(const StateType* currentState, const TransitionType& currentData) const {
	for (int i = 0; i < Transitions.size(); i++) {
		if (Transitions[i].Handles(currentState, currentData))
			return &Transitions[i];
	}

	return nullptr;
}