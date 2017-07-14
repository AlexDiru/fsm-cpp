#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "Transition.hpp"

template <typename StateType, typename TransitionType>
class FiniteStateMachine {

	using TTransition = Transition<StateType, TransitionType>;
	using TTransitions = std::vector<TTransition>;

	std::vector<const std::shared_ptr<StateType>> States; //List of all states the FSM has
	TTransitions Transitions; //List of all transitions the FSM has
	std::shared_ptr<StateType> StartState; //Starting state of the FSM

	//Used during the Consume process:
	TTransitions SingleItemTransitions;
	TTransitions MultipleItemTransitions;


	std::shared_ptr<TTransition> FindTransition(const std::shared_ptr<StateType>& currentState, const std::vector<TransitionType>& data, int& currentIndex, std::vector<std::shared_ptr<TransitionType>>& consumed) const;

	static std::vector<std::shared_ptr<TransitionType>> VectorToVectorOfPointers(const std::vector<TransitionType>& vec) {
		std::vector<std::shared_ptr<TransitionType>> vecPtr;
		for (int i = 0; i < vec.size(); i++)
			vecPtr.push_back(std::shared_ptr<TransitionType>(new TransitionType(vec[i])));
		return vecPtr;
	}
public:
	
	void AddState(const std::shared_ptr<StateType>& state);

	void SpecifyStartState(const std::shared_ptr<StateType>& start);

	void DefineTransition(const TTransition& transition) {
		//Check for existence of from state
		if (find(States.begin(), States.end(), transition.GetFromState()) == States.end())
			std::cerr << "ERROR: STATE " << *(transition.GetFromState()) << " DOES NOT EXIST" << std::endl;

		//Check for existence of to state
		if (find(States.begin(), States.end(), transition.GetToState()) == States.end())
			std::cerr << "ERROR: STATE " << *(transition.GetToState()) << " DOES NOT EXIST" << std::endl;

		Transitions.push_back(transition);
	}

	void DefineTransition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType>& to, const TransitionType& transition);
	void DefineTransition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType>& to, TransitionType&& transition);
	void DefineTransition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType>& to, const std::vector<std::shared_ptr<TransitionType>>& transitions);
	void DefineTransition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType>& to, const std::vector<TransitionType>& transitions);

	void DefineTransition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType>& to, const TransitionType& transition, const std::shared_ptr<StateType>& teleport) {
		//Check for existence of from state
		if (find(States.begin(), States.end(), from) == States.end())
			std::cerr << "ERROR: STATE " << *from << " DOES NOT EXIST" << std::endl;

		//Check for existence of to state
		if (find(States.begin(), States.end(), to) == States.end())
			std::cerr << "ERROR: STATE " << *to << " DOES NOT EXIST" << std::endl;

		if (teleport != nullptr) 
			if (find(States.begin(), States.end(), teleport) == States.end())
				std::cerr << "ERROR: STATE " << *teleport << " DOES NOT EXIST" << std::endl;

		Transitions.push_back(TTransition(from, to, std::shared_ptr<TransitionType>(new TransitionType(transition)), teleport));
	}


	void DefineTransition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType>& to, const std::vector<TransitionType>& transitions, const std::shared_ptr<StateType>& teleport) {
		DefineTransition(from, to, FiniteStateMachine::VectorToVectorOfPointers(transitions), teleport);
	}



	void DefineTransition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType> to, const std::vector<std::shared_ptr<TransitionType>>& transitions, const std::shared_ptr<StateType>& teleport) {
		//Check for existence of from state
		if (find(States.begin(), States.end(), from) == States.end())
			std::cerr << "ERROR: STATE " << *from << " DOES NOT EXIST" << std::endl;

		//Check for existence of to state
		if (find(States.begin(), States.end(), to) == States.end())
			std::cerr << "ERROR: STATE " << *to << " DOES NOT EXIST" << std::endl;

		if (teleport != nullptr) 
			if (find(States.begin(), States.end(), teleport) == States.end())
				std::cerr << "ERROR: STATE " << *teleport << " DOES NOT EXIST" << std::endl;

		Transitions.push_back(TTransition(from, to, transitions, teleport));
	}

	TTransitions Consume(const std::vector<TransitionType>& data, bool ignoreWhitespace = true, bool verbose = false);
};

#include "FiniteStateMachine.tpp"