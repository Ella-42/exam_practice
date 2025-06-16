#pragma once

#include "ATarget.hpp"
#include "ATarget.hpp"

#include <string>
#include <map>

class TargetGenerator
{
	public:
		TargetGenerator();

		void learnTargetType(ATarget const*);
		void forgetTargetType(std::string const&);

		ATarget* createTarget(std::string const&);

		~TargetGenerator();

	std::map<std::string const, ATarget const*> _targets;

	TargetGenerator(TargetGenerator const&);
	TargetGenerator& operator=(TargetGenerator const&);
};
