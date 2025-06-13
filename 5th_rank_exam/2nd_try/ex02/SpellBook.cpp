#include "SpellBook.hpp"
#include "ASpell.hpp"

#include <string>
#include <map>

SpellBook::SpellBook()
: _spells()
{}

void SpellBook::learnSpell(ASpell* spell)
{
	if (!spell)
		return ;

	this->_spells[spell->getName()] = spell;
}

void SpellBook::forgetSpell(const std::string& name)
{
	this->_spells.erase(name);
}

ASpell* SpellBook::createSpell(const std::string& name)
{
	if (name.empty() || this->_spells.find(name) == this->_spells.end())
		return NULL;

	return this->_spells[name];
}

SpellBook::~SpellBook()
{}
