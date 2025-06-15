#pragma once

#include "ATarget.hpp"

#include <iostream>
#include <map>

class TargetGenerator
{
	public:
		TargetGenerator();

		void learnTargetType(ATarget*);
		void forgetTargetType(std::string const&);

		ATarget* createTarget(std::string const&);

		~TargetGenerator();

	std::map<std::string const, ATarget*> _targets;

	TargetGenerator(TargetGenerator const&);
	TargetGenerator& operator=(TargetGenerator const&);
};
