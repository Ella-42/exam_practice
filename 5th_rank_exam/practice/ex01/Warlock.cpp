# include "Warlock.hpp" //Warlock

# include <iostream> //std::cout

Warlock::Warlock(const std::string& name, const std::string& title)
: Wizard(name, title)
{}

void Warlock::introduce(void) const
{
	std::cout << this->_name << ": *grins* They call me " << this->_name << ", " << this->_title << ". Fear me!\n";
}

void Warlock::shoutSpell(void) const
{
	std::cout << this->_name << ": 🔥 *casts Fireball* 🔥\n";
}
