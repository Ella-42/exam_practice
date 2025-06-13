#ifndef SPELLBOOK_HPP
# define SPELLBOOK_HPP

# include "ASpell.hpp"

# include <string>
# include <map>

class SpellBook
{
	public:
		SpellBook();

		void learnSpell(ASpell*);
		void forgetSpell(const std::string&);
		ASpell* createSpell(const std::string&);

		~SpellBook();
	
	std::map<const std::string, ASpell*> _spells;

	SpellBook(const SpellBook&);
	const SpellBook& operator=(const SpellBook&);
};

#endif
