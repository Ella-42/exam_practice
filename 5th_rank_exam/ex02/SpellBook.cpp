#include "SpellBook.hpp"

#include <map>
#include <string>
#include <iostream>

SpellBook::SpellBook()
{}

void SpellBook::learnSpell(ASpell* spell)
{
	if (!spell)
		return ;

	this->_spellBook[spell->getName()] = spell->clone();
}

void SpellBook::forgetSpell(const std::string& spellID)
{
	std::map<std::string, ASpell*>::iterator it;
	if (spellID.empty() || (it = this->_spellBook.find(spellID)) == this->_spellBook.end())
		return ;

	delete it->second;
	this->_spellBook.erase(it);
}

ASpell* SpellBook::createSpell(const std::string& spellID)
{
	if (spellID.empty() || this->_spellBook.find(spellID) == this->_spellBook.end())
		return (NULL);

	return (this->_spellBook[spellID]);
}

SpellBook::~SpellBook()
{
	for (std::map<std::string, ASpell*>::iterator it = this->_spellBook.begin(); it != this->_spellBook.end(); ++it)
		delete it->second;

	this->_spellBook.clear();
}
