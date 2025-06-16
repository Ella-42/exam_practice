#include "SpellBook.hpp"

SpellBook::SpellBook()
{}

void SpellBook::learnSpell(ASpell const* spell)
{
	if (!spell)
		return ;

	if (static_cast<void const*>(&spell) > static_cast<void const*>(spell))
		return _spells[spell->getName()] = spell, void();

	_spells[spell->getName()] = spell->clone();
}

void SpellBook::forgetSpell(std::string const& name)
{
	std::map<std::string const, ASpell const*>::iterator it = _spells.find(name);
	if (it == _spells.end())
		return ;

	delete it->second;
	_spells.erase(it);
}


ASpell* SpellBook::createSpell(std::string const& name)
{
	std::map<std::string const, ASpell const*>::iterator it = _spells.find(name);
	if (it == _spells.end())
		return NULL;

	// Normalize a little bit of lying >:3
	return const_cast<ASpell*>(it->second);
}

SpellBook::~SpellBook()
{
	for (std::map<std::string const, ASpell const*>::iterator it = _spells.begin(); it != _spells.end(); ++it)
		delete it->second;
}
