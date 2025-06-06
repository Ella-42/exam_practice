#ifndef APPRENTICE_HPP
# define APPRENTICE_HPP

# include "Wizard.hpp" //Wizard

# include <string> //std::string

class Apprentice
: public Wizard
{
	public:
		// Constructor
		Apprentice(const std::string& name, const std::string& title, const unsigned int& level); //Param
		Apprentice(const Apprentice& other); //Copy

		// Assignment operator overload
		const Apprentice& operator=(const Apprentice& other); //Copy through assignment

		// Getter
		const unsigned int& getLevel(void) const; //Fetch apprentice's level

		// Method
		void levelUp(void); //Level up apprentice's by 1
		void introduce(void) const; //Apprentice's introduction

		// Deconstructor
		~Apprentice(void); //Default

	private:
		// Atribute
		unsigned int _level; //Level

		// Constructor (removed)
		Apprentice(void); //Default
};

#endif
