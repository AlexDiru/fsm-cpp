#pragma once

template <typename StateType, typename TransitionType> 
Transition<StateType, TransitionType>::Transition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const shared_ptr<TransitionType> transitionValue) {
	From = from;
	To = to;
	TransitionValue = transitionValue;
}

template <typename StateType, typename TransitionType>
bool Transition<StateType, TransitionType>::Handles(shared_ptr<StateType> from,const TransitionType& data) const {
	return From == from && *TransitionValue == data;
}

template <typename StateType, typename TransitionType>
const shared_ptr<StateType> Transition<StateType, TransitionType>::GetEndState() const {
	return To;
}