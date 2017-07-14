#pragma once

#include <sstream>


//Represents the transition between states when a datum is input
//StateType: The type that the states are providing their identifier, simplest method is a string for its name
//TranisitionType: The type of data that 'feeds' the state machine (the individual items), 
//	so if its total input was a string, then this would be char
template <typename StateType, typename TransitionType>
class Transition {
	std::shared_ptr<StateType> From; //The state this transition lead from - Unnecessary?
	std::shared_ptr<StateType> To; //The state this transition leads to
	std::vector<std::shared_ptr<TransitionType>> TransitionValues; //The values this transition requires

	//Once the state is changed to To, this defines whether we will teleport back to a state (usually the start state) making state machines a lot easier to define
	std::shared_ptr<StateType> Teleport{nullptr};

public:

	Transition() = delete;

	Transition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType>& to, const std::shared_ptr<TransitionType>& transitionValue);

	Transition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType>& to, const std::vector<std::shared_ptr<TransitionType>>& transitionValues) {
		From = from;
		To = to;
		TransitionValues = transitionValues;
	}


	Transition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType>& to, const std::shared_ptr<TransitionType>& transitionValue, const std::shared_ptr<StateType>& teleport) {
		From = from;
		To = to;
		TransitionValues.push_back(transitionValue);
		Teleport = teleport;
	}

	Transition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType>& to, const std::vector<std::shared_ptr<TransitionType>>& transitionValues, const std::shared_ptr<StateType>& teleport) {
		From = from;
		To = to;
		TransitionValues = transitionValues;
		Teleport = teleport;
	}

	//Given a current state, and a data item, does this transition progress to the next state?
	bool Handles(const std::shared_ptr<StateType>& from, const TransitionType& data) const;
	bool Handles(const std::shared_ptr<StateType>& from, const std::vector<std::shared_ptr<TransitionType>>& dataVec) const;


 	bool MultipleInputsRequired() const { return TransitionValues.size() > 1; }
 	size_t GetSize() const { return TransitionValues.size(); }

 	std::string ToString(std::function<std::string(TransitionType&)> transitionTypeToStringFunction) const;

 	bool operator < (const Transition& other) const { return TransitionValues.size() < other.TransitionValues.size(); }

    const std::shared_ptr<StateType> GetFromState() const { return From; }
    const std::shared_ptr<StateType> GetToState() const { return To; }
    const std::shared_ptr<StateType> GetTeleportState() const { return Teleport; }
 	const std::shared_ptr<StateType> GetEndState() const { return To; }
};


#include "Transition.tpp"