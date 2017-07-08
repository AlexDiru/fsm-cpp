#pragma once

//Represents the transition between states when a datum is input
//StateType: The type that the states are providing their identifier, simplest method is a string for its name
//TranisitionType: The type of data that 'feeds' the state machine (the individual items), 
//	so if its total input was a string, then this would be char
template <typename StateType, typename TransitionType>
class Transition {
	const StateType *From; //The state this transition lead from - Unnecessary?
	const StateType *To; //The state this transition leads to
	const TransitionType *TransitionValue; //The value this transition requires

public:
	Transition() = delete;
	//Transition(const Transition& other);
	//Transition& operator=(const Transition& other);

	~Transition();

	Transition(const StateType *from, const StateType *to, const TransitionType* transitionValue);

	//Given a current state, and a data item, does this transition progress to the next state?
	bool Handles(const StateType *from,const TransitionType& data) const;

	//Gets the state this transition leads to
 	const StateType* GetEndState() const;
};

#include "Transition.tpp"