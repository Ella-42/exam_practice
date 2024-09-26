#include "TargetGenerator.hpp"

#include <map>
#include <string>
#include <iostream>

TargetGenerator::TargetGenerator()
{}

void TargetGenerator::learnTargetType(ATarget* target)
{
	if (!target)
		return ;

	this->_targets[target->getType()] = target->clone();
}

void TargetGenerator::forgetTargetType(const std::string& targetID)
{
	std::map<std::string, ATarget*>::iterator it;
	if (targetID.empty() || (it = this->_targets.find(targetID)) == this->_targets.end())
		return ;

	delete it->second;
	this->_targets.erase(it);
}

ATarget* TargetGenerator::createTarget(const std::string& targetID)
{
	if (targetID.empty() || this->_targets.find(targetID) == this->_targets.end())
		return (NULL);

	return (this->_targets[targetID]);
}

TargetGenerator::~TargetGenerator()
{
	for (std::map<std::string, ATarget*>::iterator it = this->_targets.begin(); it != this->_targets.end(); ++it)
		delete it->second;

	this->_targets.clear();
}
