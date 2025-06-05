#include "Wizard.hpp" //Wizard

#include <iostream> //std::cout

int main(void)
{
	Wizard harry("Harry", "the boy who lived");
	harry.introduce();
	std::cout << "Oh, hello " << harry.getName() << ", so you are " << harry.getTitle() << "...\n";

	harry.setTitle("I'm a what?");
	std::cout << "You're a wizard, " << harry.getName() << ", A WIZARD!!!\n";
	harry.introduce();
}
