#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include "ASpell.hpp"
# include "ATarget.hpp"
# include "SpellBook.hpp"

# include <string>
# include <map>

class Warlock
{
	public:
		Warlock(const std::string&, const std::string&);

		const std::string& getName() const;
		const std::string& getTitle() const;

		void setTitle(const std::string&);
		void learnSpell(ASpell*);

		void introduce() const;
		void forgetSpell(const std::string&);
		void launchSpell(const std::string&, const ATarget&);

		~Warlock();

	const std::string _name;
	std::string _title;
	SpellBook _spells;

	Warlock();
	Warlock(const Warlock&);
	const Warlock& operator= (const Warlock&);
};

#endif
