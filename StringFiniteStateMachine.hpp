#pragma once

#include <vector>

#include "FiniteStateMachine.hpp"

//This class has methods to better handle strings
class StringFiniteStateMachine : public FiniteStateMachine<std::string, char> {
public:

	using TTransition = Transition<std::string, char>;

	static const std::string A_TO_Z;
	static const std::string A_TO_z;
	static const std::string a_TO_z;
	static const std::string ZERO_TO_NINE;

	static std::vector<char> StringToVectorChar(const std::string& str);

	void DefineTransitions(std::shared_ptr<std::string> from, std::shared_ptr<std::string> to, const std::string& transitions);
	void DefineTransitions(std::shared_ptr<std::string> from, std::shared_ptr<std::string> to, const std::string& transitions, std::shared_ptr<std::string> teleportState);

	void DefineTransitions(std::shared_ptr<std::string> from, std::shared_ptr<std::string> to, std::string&& transitions);
	void DefineTransitions(std::shared_ptr<std::string> from, std::shared_ptr<std::string> to, std::string&& transitions, std::shared_ptr<std::string> teleportState);
};