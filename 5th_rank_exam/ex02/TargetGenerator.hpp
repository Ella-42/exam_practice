//#pragma once

#include <string>
#include <map>

#include "ATarget.hpp"

class ATarget;

class TargetGenerator
{
	public:
		TargetGenerator();

		void learnTargetType(ATarget* target);
		void forgetTargetType(const std::string& targetID);
		ATarget* createTarget(const std::string& targetID);

		~TargetGenerator();

	private:
		std::map<std::string, ATarget*> _targets;

		TargetGenerator(const TargetGenerator& other);

		TargetGenerator& operator= (const TargetGenerator& other);
};
