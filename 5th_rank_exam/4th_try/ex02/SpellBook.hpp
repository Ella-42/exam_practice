#pragma once

#include "ASpell.hpp"
#include "ATarget.hpp"

#include <iostream>
#include <map>

class SpellBook
{
	public:
		SpellBook();

		void learnSpell(ASpell*);
		void forgetSpell(std::string const&);

		ASpell* createSpell(std::string const&);

		~SpellBook();

	std::map<std::string const, ASpell*> _spells;

	SpellBook(SpellBook const&);
	SpellBook& operator=(SpellBook const&);
};
