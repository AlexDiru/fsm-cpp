#pragma once

#include <vector>

#include "FiniteStateMachine.hpp"

//This class has methods to better handle strings
class StringFiniteStateMachine : public FiniteStateMachine<std::string, char> {
public:

	using TTransition = Transition<std::string, char>;
	using SharedPtrString = const std::shared_ptr<std::string>&;

	static const std::string A_TO_Z;
	static const std::string A_TO_z;
	static const std::string a_TO_z;
	static const std::string ZERO_TO_NINE;

	static std::vector<char> StringToVectorChar(const std::string& str);

	void DefineTransitions(SharedPtrString from, SharedPtrString to, const std::string& transitions);
	void DefineTransitions(SharedPtrString from, SharedPtrString to, const std::string& transitions, SharedPtrString teleportState);

	void DefineTransitions(SharedPtrString from, SharedPtrString to, std::string&& transitions);
	void DefineTransitions(SharedPtrString from, SharedPtrString to, std::string&& transitions, SharedPtrString teleportState);
};