#pragma once

#include <string>

class Warlock
{
	public:
		Warlock(const std::string& name, const std::string& title);

		void setTitle(const std::string& title);

		const std::string& getName() const;
		const std::string& getTitle() const;

		void introduce() const;

		~Warlock();

	private:
		std::string _name;
		std::string _title;

		Warlock();
		Warlock(const Warlock& other);

		Warlock& operator= (const Warlock& other);
};
