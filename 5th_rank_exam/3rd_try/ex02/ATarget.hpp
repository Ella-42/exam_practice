#pragma once

#include "ASpell.hpp"

#include <string>
#include <iostream>

class ASpell;

class ATarget
{
	public:
		ATarget();
		ATarget(std::string const&);

		ATarget(ATarget const&);
		ATarget& operator=(ATarget const&);

		std::string getType() const;

		virtual ATarget* clone() const = 0;
		void getHitBySpell(ASpell const&) const;

		virtual ~ATarget();

	protected:
		std::string type;
};
