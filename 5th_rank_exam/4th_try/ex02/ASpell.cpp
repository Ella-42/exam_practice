#include "ASpell.hpp"

ASpell::ASpell()
: name("undefined"), effects("undefined")
{}

ASpell::ASpell(std::string const& name, std::string const& effects)
: name(name), effects(effects)
{}

ASpell::ASpell(ASpell const& other)
: name(other.name), effects(other.effects)
{}

ASpell& ASpell::operator=(ASpell const& other)
{
	if (this != &other)
	{
		name = other.name;
		effects = other.effects;
	}

	return *this;
}

std::string const& ASpell::getName() const
{
	return name;
}

std::string const& ASpell::getEffects() const
{
	return effects;
}

void ASpell::launch(ATarget const& target) const
{
	target.getHitBySpell(*this);
}

ASpell::~ASpell()
{}
