#include "Wizard.hpp" //Wizard
#include "Warlock.hpp" //Warlock
#include "Apprentice.hpp" //Warlock

#include <iostream> //std::cout

int main(void)
{
	Wizard harry("Harry", "the boy who lived");
	harry.introduce();
	std::cout << "Oh, hello " << harry.getName() << ", so you are " << harry.getTitle() << "...\n";

	harry.setTitle("I'm a what?");
	std::cout << "You're a wizard, " << harry.getName() << ", A WIZARD!!!\n";
	harry.introduce();

	Warlock tom("Tom", "the cursed one");
	tom.introduce();
	tom.shoutSpell();

	Apprentice hermione("Hermione", "hella studious", 5);
	hermione.introduce();

	hermione.levelUp();
	hermione.introduce();
	std::cout << hermione.getName() << ": Oh, I just leveled up to level " << hermione.getLevel() << "!\n";

        Apprentice copyHermione(hermione);
        copyHermione.introduce();

        Apprentice ron("Ron", "reluctant ginger", 2);
        ron.introduce();

        ron = hermione;
        ron.introduce();
}
