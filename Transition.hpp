#pragma once

#include <sstream>

using namespace std;


//Represents the transition between states when a datum is input
//StateType: The type that the states are providing their identifier, simplest method is a string for its name
//TranisitionType: The type of data that 'feeds' the state machine (the individual items), 
//	so if its total input was a string, then this would be char
template <typename StateType, typename TransitionType>
class Transition {
	shared_ptr<StateType> From; //The state this transition lead from - Unnecessary?
	shared_ptr<StateType> To; //The state this transition leads to
	vector<shared_ptr<TransitionType>> TransitionValues; //The values this transition requires

	//Once the state is changed to To, this defines whether we will teleport back to a state (usually the start state) making state machines a lot easier to define
	shared_ptr<StateType> Teleport{nullptr};

public:

	Transition() = delete;

	Transition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const shared_ptr<TransitionType> transitionValue);

	Transition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const vector<shared_ptr<TransitionType>>& transitionValues) {
		From = from;
		To = to;
		TransitionValues = transitionValues;
	}


	Transition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const shared_ptr<TransitionType> transitionValue, const shared_ptr<StateType> teleport) {
		From = from;
		To = to;
		TransitionValues.push_back(transitionValue);
		Teleport = teleport;
	}

	Transition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const vector<shared_ptr<TransitionType>>& transitionValues, const shared_ptr<StateType> teleport) {
		From = from;
		To = to;
		TransitionValues = transitionValues;
		Teleport = teleport;
	}

	//Given a current state, and a data item, does this transition progress to the next state?
	bool Handles(shared_ptr<StateType> from, const TransitionType& data) const;

	bool Handles(shared_ptr<StateType> from, const vector<shared_ptr<TransitionType>>& dataVec) const;

	//Gets the state this transition leads to
 	const shared_ptr<StateType> GetEndState() const;

 	bool MultipleInputsRequired() const {
 		return TransitionValues.size() > 1;
 	}

 	size_t GetSize() const {
 		return TransitionValues.size();
 	}

 	string ToString(function<string(TransitionType&)> transitionTypeToStringFunction) const {

 		//Use stringstreams?
 		string str{*To};
 		str += " (";
 		
 		for (size_t i  = 0; i < TransitionValues.size(); i++) 
 			str += transitionTypeToStringFunction(*(TransitionValues[i]));
 		
 		str += ")";
		return str;
 	}

 	bool operator < (const Transition& other) const
    {
        return TransitionValues.size() < other.TransitionValues.size();
    }

    const shared_ptr<StateType> GetFromState() const {
    	return From;
    }

    const shared_ptr<StateType> GetToState() const {
    	return To;
    }

    const shared_ptr<StateType> GetTeleportState() const {
    	return Teleport;
    }
};


#include "Transition.tpp"