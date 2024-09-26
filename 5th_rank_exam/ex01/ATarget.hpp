#pragma once

#include "ASpell.hpp"

#include <string>

class ASpell;

class ATarget
{
	public:
		ATarget(const std::string& type);
		ATarget(const ATarget& other);

		ATarget& operator= (const ATarget& other);

		const std::string& getType() const;

		virtual ATarget* clone() const = 0;

		void getHitBySpell(const ASpell& spell) const;

		virtual ~ATarget();

	protected:
		std::string type;
};
