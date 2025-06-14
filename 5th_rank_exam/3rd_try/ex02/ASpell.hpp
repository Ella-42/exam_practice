#pragma once

#include "ATarget.hpp"

#include <string>

class ATarget;

class ASpell
{
	public:
		ASpell();
		ASpell(std::string const&, std::string const&);

		ASpell(ASpell const&);
		ASpell& operator=(ASpell const&);

		std::string getName() const;
		std::string getEffects() const;

		virtual ASpell* clone() const = 0;
		void launch(ATarget const&) const;

		virtual ~ASpell();

	protected:
		std::string name;
		std::string effects;
};
