#pragma once

template <typename StateType, typename TransitionType> 
Transition<StateType, TransitionType>::Transition(const StateType *from, const StateType *to, const TransitionType* transitionValue) {
	From = from;
	To = to;
	TransitionValue = transitionValue;
}

template <typename StateType, typename TransitionType>
bool Transition<StateType, TransitionType>::Handles(const StateType *from,const TransitionType& data) const {
	return From == from && *TransitionValue == data;
}

template <typename StateType, typename TransitionType>
const StateType* Transition<StateType, TransitionType>::GetEndState() const {
	return To;
}

