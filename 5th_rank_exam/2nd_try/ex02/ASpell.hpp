#ifndef ASPELL_HPP
# define ASPELL_HPP

# include "ATarget.hpp"

# include <string>

class ATarget;

class ASpell
{
	public:
		ASpell();
		ASpell(const std::string&, const std::string&);

		ASpell(const ASpell&);
		const ASpell& operator=(const ASpell&);

		const std::string& getName() const;
		const std::string& getEffects() const;

		virtual ASpell* clone() const = 0;
		void launch(const ATarget&) const;

		virtual ~ASpell();

	protected:
		std::string name;
		std::string effects;
};

#endif
