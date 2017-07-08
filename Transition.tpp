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

template <typename StateType, typename TransitionType> 
Transition<StateType, TransitionType>::~Transition() {
	//if (From != nullptr)
	//	delete From;
	//if (To != nullptr)
	//	delete To;
	//if (TransitionValue != nullptr)
	//	delete TransitionValue;
}

/*template <typename StateType, typename TransitionType> 
Transition<StateType, TransitionType>::Transition(const Transition& other) {
	From = new StateType(*other.From);
	To = new StateType(*other.To);
	TransitionValue = new TransitionType(*other.TransitionValue);
}

template <typename StateType, typename TransitionType> 
Transition<StateType, TransitionType>& Transition<StateType, TransitionType>::operator=(const Transition& other) {
	From = new StateType(*other.From);
	To = new StateType(*other.To);
	TransitionValue = new TransitionType(*other.TransitionValue);
	return *this;
}*/
