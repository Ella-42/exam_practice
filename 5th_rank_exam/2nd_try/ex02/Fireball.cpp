#include "Fireball.hpp"
#include "ASpell.hpp"

Fireball::Fireball()
: ASpell("Fireball", "burnt to a crisp")
{}

ASpell* Fireball::clone() const
{
	return new Fireball();
}

Fireball::~Fireball()
{}
