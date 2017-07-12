#pragma once

template <typename StateType, typename TransitionType>
vector<Transition<StateType, TransitionType>> FiniteStateMachine<StateType, TransitionType>::Consume(const vector<TransitionType>& data, bool ignoreWhitespace, bool verbose) {

	//Sort transitions by length, prioritising longer ones
	//This way we can have 334 and 33 has state changers
	sort(Transitions.begin(), Transitions.end(), [](const TTransition& a, const TTransition& b) -> bool { return a.GetSize() > b.GetSize(); });
	
	shared_ptr<StateType> currentState = StartState;
	shared_ptr<StateType> previousState = StartState;
	TTransitions stateChanges;

	if (verbose) {
		cout << "Consume Input: ";
		for (int i = 0; i < data.size(); i++)
			cout << data[i];
		cout << endl;
	}

	int i = 0;
	while(i < data.size()) {

		if (ignoreWhitespace && data[i] == ' ') {
			i++;
			continue;
		}

		if (verbose) {
			cout << "Current State: " << *currentState << endl;
		}

		int prevIndex = i;

		vector<shared_ptr<TransitionType>> consumed;
		auto transition = FindTransition(currentState, data, i, consumed); //This function modifies i

		if (transition == nullptr) {
			cerr << "ERROR: TRANSITION NOT FOUND INVALID INPUT, EXITING CONSUME()" << endl;
			return stateChanges;
		} else {
			previousState = currentState;
			currentState = transition->GetEndState();
			stateChanges.push_back(TTransition(previousState, currentState, consumed));

			//Teleport
			if (transition->GetTeleportState() != nullptr) 
				currentState = transition->GetTeleportState();
		}

	}

	if (verbose)
		cout << "Final State: " << *currentState << endl;

	return stateChanges;
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::AddState(const shared_ptr<StateType> state) {
	States.push_back(state);
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::SpecifyStartState(shared_ptr<StateType> start) {
	StartState = start;
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const TransitionType& transition) {
	DefineTransition(from, to, transition, nullptr);
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, TransitionType&& transition) {
	TransitionType temp = transition;
	DefineTransition(from, to, transition);
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const vector<shared_ptr<TransitionType>>& transitions) {
	DefineTransition(from, to, transitions, nullptr);
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::DefineTransition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const vector<TransitionType>& transitions) {
	DefineTransition(from, to, transitions, nullptr);
}

template <typename StateType, typename TransitionType>
shared_ptr<Transition<StateType, TransitionType>> FiniteStateMachine<StateType, TransitionType>::FindTransition(const shared_ptr<StateType> currentState, const vector<TransitionType>& data, int& currentIndex, vector<shared_ptr<TransitionType>>& consumed) const {

	for (int i = 0; i < Transitions.size(); i++) {
		size_t transitionSize = Transitions[i].GetSize();

		//There is not enough data left for this transition
		if (currentIndex + transitionSize > data.size())
			continue;

		vector<shared_ptr<TransitionType>> dataSubset;
		for (int j = currentIndex; j < currentIndex + transitionSize; j++) 
			dataSubset.push_back(shared_ptr<TransitionType>(new TransitionType(data[j])));
			
		if (Transitions[i].Handles(currentState, dataSubset)) {
			currentIndex += Transitions[i].GetSize();
			consumed = dataSubset;
			return shared_ptr<Transition<StateType, TransitionType>>(new Transition<StateType, TransitionType>(Transitions[i]));
		}
	}

	return nullptr;
}