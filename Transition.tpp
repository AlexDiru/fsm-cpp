#pragma once

template <typename StateType, typename TransitionType> 
Transition<StateType, TransitionType>::Transition(const std::shared_ptr<StateType>& from, const std::shared_ptr<StateType>& to, const std::shared_ptr<TransitionType>& transitionValue) {
	From = from;
	To = to;
	TransitionValues.push_back(transitionValue);
}

//ONLY FOR SINGLE ELEMENT TRANSITIONS
template <typename StateType, typename TransitionType>
bool Transition<StateType, TransitionType>::Handles(const std::shared_ptr<StateType>& from,const TransitionType& data) const {
	if (TransitionValues.size() != 1)
		return false;

	return From == from && *TransitionValues[0] == data;
}

template <typename StateType, typename TransitionType>
bool Transition<StateType, TransitionType>::Handles(const std::shared_ptr<StateType>& from,const std::vector<std::shared_ptr<TransitionType>>& dataVec) const {


	if (TransitionValues.size() == 0)
		std::cerr << "No Transition Values for Transition" << std::endl;

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
std::string Transition<StateType, TransitionType>::ToString(std::function<std::string(TransitionType&)> transitionTypeToStringFunction) const {

	//Use stringstreams?
	std::string str{*To};
	str += " (";
	
	for (size_t i  = 0; i < TransitionValues.size(); i++) 
		str += transitionTypeToStringFunction(*(TransitionValues[i]));
	
	str += ")";
	return str;
}