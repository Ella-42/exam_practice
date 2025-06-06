#include "Wizard.hpp" //Wizard

#include <string> //std::string
#include <iostream> //std::cout

// Constructor for Wizard
Wizard::Wizard(const std::string& name, const std::string& title)
: _name(name), _title(title)
{}

// Getter for name
const std::string& Wizard::getName(void) const
{
	return (this->_name);
}

// Getter for title
const std::string& Wizard::getTitle(void) const
{
	return (this->_title);
}

// Setter for title
void Wizard::setTitle(const std::string& title)
{
	this->_title = title;
}

// Wizard introduces themself
void Wizard::introduce(void) const
{
	std::cout << this->_name << ": I am " << this->_name << ", " << this->_title << "!\n";
}

Wizard::~Wizard(){}
