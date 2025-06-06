#include "Wizard.hpp" //Wizard
#include "Apprentice.hpp" //Apprentice

#include <string> //std::string
#include <iostream> //std::cout

Apprentice::Apprentice(const std::string& name, const std::string& title, const unsigned int& level)
: Wizard(name, title), _level(level)
{}

Apprentice::Apprentice(const Apprentice& other)
: Wizard(other.getName(), other.getTitle()), _level(other.getLevel())
{}

const Apprentice& Apprentice::operator=(const Apprentice& other)
{
	if (this != &other)
	{
		this->_name = other.getName();
		this->_title = other.getTitle();
		this->_level = other.getLevel();
	}

	return (*this);
}

const unsigned int& Apprentice::getLevel(void) const
{
	return (this->_level);
}

void Apprentice::levelUp(void)
{
	this->_level += 1;
}

void Apprentice::introduce(void) const
{
	std::cout << this->_name << ": Hello, I am Apprentice " << this->_name << ", level " << this->_level << ", also known as " << this->_title << ".\n";
}

Apprentice::~Apprentice(void)
{}
