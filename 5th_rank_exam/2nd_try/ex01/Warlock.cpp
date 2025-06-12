#include "Warlock.hpp"
#include "ASpell.hpp"
#include "ATarget.hpp"

#include <string>
#include <iostream>

Warlock::Warlock(const std::string& name, const std::string& title)
: _name(name), _title(title)
{
	std::cout << this->_name << ": This looks like another boring day.\n";
}

const std::string& Warlock::getName() const
{
	return (this->_name);
}

const std::string& Warlock::getTitle() const
{
	return (this->_title);
}

void Warlock::learnSpell(ASpell* spell)
{
	const std::string& name = spell->getName();

	if (this->_spells.find(name) == this->_spells.end())
		this->_spells[name] = spell;
}

void Warlock::setTitle(const std::string& title)
{
	this->_title = title;
}

void Warlock::introduce() const
{
	std::cout << this->_name << ": I am " << this->_name << ", " << this->_title << "!\n";
}

void Warlock::forgetSpell(const std::string& name)
{
	this->_spells.erase(name);
}

void Warlock::launchSpell(const std::string& name, const ATarget& target)
{
	std::map<std::string, ASpell*>::iterator it = this->_spells.find(name);

	if (it != this->_spells.end())
		this->_spells[name]->launch(target);
}

Warlock::~Warlock()
{
	std::cout << this->_name << ": My job here is done!\n";
}
