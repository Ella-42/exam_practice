#ifndef WIZARD_HPP
# define WIZARD_HPP

# include <string> //std::string

class Wizard
{
	public:
		// Constructor
		Wizard(const std::string& name, const std::string& title);

		// Getter
		const std::string& getName(void) const;
		const std::string& getTitle(void) const;

		// Setter
		void setTitle(const std::string& title);

		// Method
		void introduce(void) const;

		// Deconstructor
		~Wizard(void);

	private:
		// Attributes
		const std::string _name;
		std::string _title;

		// Deleted methods
		Wizard();
		Wizard(const Wizard& wizard);
		Wizard& operator=(const Wizard& wizard);
};

#endif
