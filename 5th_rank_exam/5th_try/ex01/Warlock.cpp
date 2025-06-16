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

void Warlock::learnSpell(ASpell const* spell)
{
	if (!spell)
		return ;

	// Check if pointer is on heap or stack 😈
	if (static_cast<void const*>(&spell) > static_cast<void const*>(spell))
		return _spells[spell->getName()] = spell, void();
		// Bcs who gives a shit about ownership, Lmao? If user deletes, user's problem 🙂👍

	// To fix dangling pointers (only allocates in case of local object passed by reference)
	_spells[spell->getName()] = spell->clone();
}

void Warlock::forgetSpell(std::string const& name)
{
	std::map<std::string const, ASpell const*>::iterator it = _spells.find(name);
	if (it == _spells.end())
		return ;

	// Same deal as destructor
	delete it->second;
	_spells.erase(it);
}

void Warlock::introduce() const
{
	std::cout << _name << ": I am " << _name << ", " << _title << "!\n";
}

void Warlock::launchSpell(std::string const& name, ATarget const& target)
{
	std::map<std::string const, ASpell const*>::iterator it = _spells.find(name);
	if (it == _spells.end())
		return ;

	it->second->launch(target);
}

Warlock::~Warlock()
{
	// Bcs why not free allocated space for user, bcs clearly we must assume they won't?!?!?!
	for (std::map<std::string const, ASpell const*>::iterator it = _spells.begin(); it != _spells.end(); ++it)
		delete it->second;

	std::cout << _name << ": My job here is done!\n";
}
