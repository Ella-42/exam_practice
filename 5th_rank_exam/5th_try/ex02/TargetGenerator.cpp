#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator()
{}

void TargetGenerator::learnTargetType(ATarget const* target)
{
	if (!target)
		return ;

	if (static_cast<void const*>(&target) > static_cast<void const*>(target))
		return _targets[target->getType()] = target, void();

	_targets[target->getType()] = target->clone();
}

void TargetGenerator::forgetTargetType(std::string const& type)
{
	std::map<std::string const, ATarget const*>::iterator it = _targets.find(type);
	if (it == _targets.end())
		return ;

	delete it->second;
	_targets.erase(it);
}


ATarget* TargetGenerator::createTarget(std::string const& type)
{
	std::map<std::string const, ATarget const*>::iterator it = _targets.find(type);
	if (it == _targets.end())
		return NULL;

	// We simply... lie
	return const_cast<ATarget*>(it->second);
}

TargetGenerator::~TargetGenerator()
{
	for (std::map<std::string const, ATarget const*>::iterator it = _targets.begin(); it != _targets.end(); ++it)
		delete it->second;
}
