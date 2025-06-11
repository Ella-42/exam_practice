#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <string>

class Warlock
{
	public:
		Warlock(const std::string&, const std::string&);

		const std::string& getName() const;
		const std::string& getTitle() const;

		void setTitle(const std::string&);

		void introduce() const;

		~Warlock();

	const std::string _name;
	std::string _title;

	Warlock();
	Warlock(const Warlock&);
	const Warlock& operator= (const Warlock&);
};

#endif
