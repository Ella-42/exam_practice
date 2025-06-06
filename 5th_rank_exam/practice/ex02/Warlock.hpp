#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include "Wizard.hpp" //Wizard

# include <string> //std::string

class Warlock
: public Wizard
{
	public:
		// Constructor
		Warlock(const std::string& name, const std::string& title);

		// Method
		void introduce(void) const;
		void shoutSpell(void) const;
};

#endif
