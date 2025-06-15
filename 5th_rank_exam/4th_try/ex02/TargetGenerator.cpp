#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator()
: _targets()
{}

void TargetGenerator::learnTargetType(ATarget* target)
{
	if (target)
		_targets[target->getType()] = target->clone();
}

void TargetGenerator::forgetTargetType(std::string const& type)
{
	std::map<std::string const, ATarget*>::iterator it = _targets.find(type);
	if (it == _targets.end())
		return ;

	delete it->second;
	_targets.erase(it);
}

ATarget* TargetGenerator::createTarget(std::string const& type)
{
	std::map<std::string const, ATarget*>::iterator it = _targets.find(type);
	if (it == _targets.end())
		return NULL;

	return it->second->clone();
}

TargetGenerator::~TargetGenerator()
{
	for (std::map<std::string const, ATarget*>::iterator it = _targets.begin(); it != _targets.end(); ++it)
		delete it->second;
}
