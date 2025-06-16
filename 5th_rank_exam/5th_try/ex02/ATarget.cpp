#include "ATarget.hpp"

ATarget::ATarget()
: type("undefined")
{}

ATarget::ATarget(std::string const& type)
: type(type)
{}

ATarget::ATarget(ATarget const& other)
: type(other.type)
{}

ATarget& ATarget::operator=(ATarget const& other)
{
	if (this != &other)
		type = other.type;

	return *this;
}

std::string const& ATarget::getType() const
{
	return type;
}

void ATarget::getHitBySpell(ASpell const& spell) const
{
	std::cout << type << " has been " << spell.getEffects() << "!\n";
}

ATarget::~ATarget()
{}
