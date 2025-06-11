#pragma once

#include <string>
#include <map>

#include "ASpell.hpp"

class ASpell;

class Warlock
{
	public:
		Warlock(const std::string& name, const std::string& title);

		void setTitle(const std::string& title);

		const std::string& getName() const;
		const std::string& getTitle() const;

		void introduce() const;

		void learnSpell(ASpell* spell);
		void forgetSpell(std::string spellID);
		void launchSpell(std::string spellID, const ATarget& target);

		~Warlock();

	private:
		std::string _name;
		std::string _title;
		std::map<std::string, ASpell*> _spellBook;

		Warlock();
		Warlock(const Warlock& other);

		Warlock& operator= (const Warlock& other);
};
