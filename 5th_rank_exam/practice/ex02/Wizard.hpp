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
		virtual void introduce(void) const;

		// Deconstructor
		virtual ~Wizard(void);

	protected:
		// Attributes
		std::string _name;
		std::string _title;

		// Deleted methods
		Wizard();
		Wizard(const Wizard& other);
		Wizard& operator=(const Wizard& other);
};

#endif
