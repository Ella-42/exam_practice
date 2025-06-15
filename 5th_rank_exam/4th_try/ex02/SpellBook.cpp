#include "SpellBook.hpp"

SpellBook::SpellBook()
: _spells()
{}

void SpellBook::learnSpell(ASpell* spell)
{
	if (spell)
		_spells[spell->getName()] = spell->clone();
}

void SpellBook::forgetSpell(std::string const& name)
{
	std::map<std::string const, ASpell*>::iterator it = _spells.find(name);
	if (it == _spells.end())
		return ;

	delete it->second;
	_spells.erase(it);
}

ASpell* SpellBook::createSpell(std::string const& name)
{
	std::map<std::string const, ASpell*>::iterator it = _spells.find(name);
	if (it == _spells.end())
		return NULL;

	return it->second->clone();
}

SpellBook::~SpellBook()
{
	for (std::map<std::string const, ASpell*>::iterator it = _spells.begin(); it != _spells.end(); ++it)
		delete it->second;
}
