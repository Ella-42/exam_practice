#include "Warlock.hpp"

Warlock::Warlock(std::string const& name, std::string const& title)
: _name(name), _title(title)
{
	std::cout << _name << ": This looks like another boring day.\n";
}

std::string const& Warlock::getName() const
{
	return _name;
}

std::string const& Warlock::getTitle() const
{
	return _title;
}

void Warlock::setTitle(std::string const& title)
{
	_title = title;
}

void Warlock::learnSpell(ASpell* spell)
{
	if (spell)
		_spells[spell->getName()] = spell->clone();
}

void Warlock::forgetSpell(std::string const& name)
{
	std::map<std::string const, ASpell*>::iterator it = _spells.find(name);
	if (it == _spells.end())
		return ;

	delete it->second;
	_spells.erase(it);
}

void Warlock::introduce() const
{
	std::cout << _name << ": I am " << _name << ", " << _title << "!\n";
}

void Warlock::launchSpell(std::string const& name, ATarget const& target)
{
	std::map<std::string const, ASpell*>::iterator it = _spells.find(name);
	if (it == _spells.end())
		return ;

	it->second->launch(target);
}

Warlock::~Warlock()
{
	for (std::map<std::string const, ASpell*>::iterator it = _spells.begin(); it != _spells.end(); ++it)
		delete it->second;

	std::cout << _name << ": My job here is done!\n";
}
