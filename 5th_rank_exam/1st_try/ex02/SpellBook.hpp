//#pragma once

#include <string>
#include <map>

#include "ASpell.hpp"

class ASpell;

class SpellBook
{
	public:
		SpellBook();

		void learnSpell(ASpell* spell);
		void forgetSpell(const std::string& spellID);
		ASpell* createSpell(const std::string& spellID);

		~SpellBook();

	private:
		std::map<std::string, ASpell*> _spellBook;

		SpellBook(const SpellBook& other);

		SpellBook& operator= (const SpellBook& other);
};
