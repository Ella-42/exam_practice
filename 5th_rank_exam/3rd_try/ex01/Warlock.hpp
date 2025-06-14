#pragma once

#include "ASpell.hpp"

#include <string>
#include <iostream>
#include <map>

class Warlock
{
	public:
		Warlock(std::string const&, std::string const&);

		std::string const& getName() const;
		std::string const& getTitle() const;

		void setTitle(std::string const&);
		void learnSpell(ASpell*);
		void forgetSpell(std::string const&);

		void introduce() const;
		void launchSpell(std::string const&, ATarget const&);

		~Warlock();

	std::string const _name;
	std::string _title;
	std::map<std::string const, ASpell*> _spells;

	Warlock();
	Warlock(Warlock const&);
	Warlock & operator=(Warlock const&);
};
