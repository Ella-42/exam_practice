#include "Warlock.hpp"

#include <string>
#include <iostream>

Warlock::Warlock(const std::string& name, const std::string& title)
: _name(name), _title(title)
{
	std::cout << this->_name << ": This looks like another boring day.\n";
}

void Warlock::setTitle(const std::string& title)
{
	this->_title = title;
}

const std::string& Warlock::getName() const
{
	return (this->_name);
}

const std::string& Warlock::getTitle() const
{
	return (this->_title);
}

void Warlock::introduce() const
{
	std::cout << this->_name << ": I am " << this->_name << ", " << this->_title << "!\n";
}

void Warlock::learnSpell(ASpell* spell)
{
	if (!spell || this->_spellBook.find(spell->getName()) != this->_spellBook.end())
		return ;

	this->_spellBook[spell->getName()] = spell->clone();

	if (static_cast<void*>(spell) < static_cast<void*>(&spell))
    	delete spell;
}

void Warlock::forgetSpell(std::string spellID)
{
	std::map<std::string, ASpell*>::iterator it;
	if (spellID.empty() || (it = this->_spellBook.find(spellID)) == this->_spellBook.end())
		return ;

	delete it->second;
	this->_spellBook.erase(it);
}

void Warlock::launchSpell(std::string spellID, const ATarget& target)
{
	if (spellID.empty() || this->_spellBook.find(spellID) == this->_spellBook.end())
		return ;

	this->_spellBook[spellID]->launch(target);
}

Warlock::~Warlock()
{
	for (std::map<std::string, ASpell*>::iterator it = this->_spellBook.begin(); it != this->_spellBook.end(); ++it)
		delete it->second;

	this->_spellBook.clear();

	std::cout << this->_name << ": My job here is done!\n";
}
