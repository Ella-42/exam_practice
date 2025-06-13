#include "TargetGenerator.hpp"
#include "ATarget.hpp"

#include <string>
#include <map>

TargetGenerator::TargetGenerator()
: _targets()
{}

void TargetGenerator::learnTargetType(ATarget* target)
{
	this->_targets[target->getType()] = target;
}

void TargetGenerator::forgetTargetType(const std::string& name)
{
	this->_targets.erase(name);
}

ATarget* TargetGenerator::createTarget(const std::string& name)
{
	if (this->_targets.find(name) == this->_targets.end())
		return NULL;

	return this->_targets[name];
}

TargetGenerator::~TargetGenerator()
{}
