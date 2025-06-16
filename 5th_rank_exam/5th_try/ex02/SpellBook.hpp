#pragma once

#include "ASpell.hpp"
#include "ATarget.hpp"

#include <string>
#include <map>

class SpellBook
{
	public:
		SpellBook();

		void learnSpell(ASpell const*);
		void forgetSpell(std::string const&);

		ASpell* createSpell(std::string const&);

		~SpellBook();

	std::map<std::string const, ASpell const*> _spells;

	SpellBook(SpellBook const&);
	SpellBook& operator=(SpellBook const&);
};
