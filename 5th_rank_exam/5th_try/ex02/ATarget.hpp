#pragma once

#include "ASpell.hpp"

#include <iostream>

class ASpell;

class ATarget
{
	public:
		ATarget();
		ATarget(std::string const&);

		ATarget(ATarget const&);
		ATarget& operator=(ATarget const&);

		std::string const& getType() const;

		void getHitBySpell(ASpell const&) const;
		virtual ATarget const* clone() const = 0;

		virtual ~ATarget();

	protected:
		std::string type;
};
