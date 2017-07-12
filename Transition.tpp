#pragma once

template <typename StateType, typename TransitionType> 
Transition<StateType, TransitionType>::Transition(const shared_ptr<StateType> from, const shared_ptr<StateType> to, const shared_ptr<TransitionType> transitionValue) {
	From = from;
	To = to;
	TransitionValues.push_back(transitionValue);
}

//ONLY FOR SINGLE ELEMENT TRANSITIONS
template <typename StateType, typename TransitionType>
bool Transition<StateType, TransitionType>::Handles(shared_ptr<StateType> from,const TransitionType& data) const {
	if (TransitionValues.size() != 1)
		return false;

	return From == from && *TransitionValues[0] == data;
}

template <typename StateType, typename TransitionType>
bool Transition<StateType, TransitionType>::Handles(shared_ptr<StateType> from,const vector<shared_ptr<TransitionType>>& dataVec) const {


	if (TransitionValues.size() == 0)
		cerr << "No Transition Values for Transition" << endl;

	if (dataVec.size() != TransitionValues.size())
		return false;

	if (From != from)
		return false;

	//Multiple element transition (1 -> INF)
	bool same = true;
	for (int i = 0; i < dataVec.size(); i++) {
		if (*TransitionValues[i] != *(dataVec[i])) {
			same = false;
			break;
		}
	}

	return same;
}

template <typename StateType, typename TransitionType>
const shared_ptr<StateType> Transition<StateType, TransitionType>::GetEndState() const {
	return To;
}