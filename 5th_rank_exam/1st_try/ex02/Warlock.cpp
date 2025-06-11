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
	this->_spellBook.learnSpell(spell);
}

void Warlock::forgetSpell(std::string spellID)
{
	this->_spellBook.forgetSpell(spellID);
}

void Warlock::launchSpell(std::string spellID, const ATarget& target)
{
	ASpell* spell = this->_spellBook.createSpell(spellID);
	if (!spell)
		return ;

	spell->launch(target);
}

Warlock::~Warlock()
{
	std::cout << this->_name << ": My job here is done!\n";
}
