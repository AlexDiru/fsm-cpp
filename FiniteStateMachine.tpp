#pragma once

template <typename StateType, typename TransitionType>
std::vector<Transition<StateType, TransitionType>> FiniteStateMachine<StateType, TransitionType>::Consume(const std::vector<TransitionType>& data, bool ignoreWhitespace, bool verbose) {

	//Sort transitions by length, prioritising longer ones
	//This way we can have 334 and 33 has state changers
	sort(Transitions.begin(), Transitions.end(), [](const TTransition& a, const TTransition& b) -> bool { return a.GetSize() > b.GetSize(); });
	
	std::shared_ptr<StateType> currentState = StartState;
	std::shared_ptr<StateType> previousState = StartState;
	TTransitions stateChanges;

	if (verbose) {
		std::cout << "Consume Input: ";
		for (int i = 0; i < data.size(); i++)
			std::cout << data[i];
		std::cout << std::endl;
	}

	int i = 0;
	while(i < data.size()) {

		if (ignoreWhitespace && data[i] == ' ') {
			i++;
			continue;
		}

		if (verbose) {
			std::cout << "Current State: " << *currentState << std::endl;
		}

		int prevIndex = i;

		std::vector<std::shared_ptr<TransitionType>> consumed;
		auto transition = FindTransition(currentState, data, i, consumed); //This function modifies i

		if (transition == nullptr) {
			std::cerr << "ERROR: TRANSITION NOT FOUND INVALID INPUT, EXITING CONSUME()" << std::endl;
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
		std::cout << "Final State: " << *currentState << std::endl;

	return stateChanges;
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::AddState(const std::shared_ptr<StateType>& state) {
	States.push_back(state);
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::SpecifyStartState(const std::shared_ptr<StateType>& start) {
	StartState = start;
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::DefineTransition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType>& to, const TransitionType& transition) {
	DefineTransition(from, to, transition, nullptr);
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::DefineTransition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType>& to, TransitionType&& transition) {
	TransitionType temp = transition;
	DefineTransition(from, to, transition);
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::DefineTransition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType>& to, const std::vector<std::shared_ptr<TransitionType>>& transitions) {
	DefineTransition(from, to, transitions, nullptr);
}

template <typename StateType, typename TransitionType>
void FiniteStateMachine<StateType, TransitionType>::DefineTransition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType>& to, const std::vector<TransitionType>& transitions) {
	DefineTransition(from, to, transitions, nullptr);
}

template <typename StateType, typename TransitionType>
std::shared_ptr<Transition<StateType, TransitionType>> FiniteStateMachine<StateType, TransitionType>::FindTransition(const std::shared_ptr<StateType>& currentState, const std::vector<TransitionType>& data, int& currentIndex, std::vector<std::shared_ptr<TransitionType>>& consumed) const {

	for (int i = 0; i < Transitions.size(); i++) {
		size_t transitionSize = Transitions[i].GetSize();

		//There is not enough data left for this transition
		if (currentIndex + transitionSize > data.size())
			continue;

		std::vector<std::shared_ptr<TransitionType>> dataSubset;
		for (int j = currentIndex; j < currentIndex + transitionSize; j++) 
			dataSubset.push_back(std::shared_ptr<TransitionType>(new TransitionType(data[j])));
			
		if (Transitions[i].Handles(currentState, dataSubset)) {
			currentIndex += Transitions[i].GetSize();
			consumed = dataSubset;
			return std::shared_ptr<Transition<StateType, TransitionType>>(new Transition<StateType, TransitionType>(Transitions[i]));
		}
	}

	return nullptr;
}