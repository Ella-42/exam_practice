#include "Warlock.hpp"
#include "Dummy.hpp"
#include "Fwoosh.hpp"

#include <iostream>

int main()
{
  Warlock richard("Richard", "the Titled");

  Dummy bob;
  //Fwoosh *fwoosh = new Fwoosh();
  Fwoosh fwoosh = Fwoosh();

  //richard.learnSpell(fwoosh);
  richard.learnSpell(&fwoosh);

  richard.introduce();
  richard.launchSpell("Fwoosh", bob);

  richard.forgetSpell("Fwoosh");
  richard.launchSpell("Fwoosh", bob);

  // Not part of the subject, but obviously necessary
  //delete fwoosh;
}
