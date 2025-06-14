#pragma once

#include <string>
#include <iostream>

class Warlock
{
	public:
		Warlock(std::string const&, std::string const&);

		std::string const& getName() const;
		std::string const& getTitle() const;

		void setTitle(std::string const&);

		void introduce() const;

		~Warlock();

	std::string const _name;
	std::string _title;

	Warlock();
	Warlock(Warlock const&);
	Warlock & operator=(Warlock const&);
};
