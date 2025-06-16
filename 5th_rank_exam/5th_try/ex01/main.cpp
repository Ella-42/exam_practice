#include "Warlock.hpp"
#include "Fwoosh.hpp"
#include "Dummy.hpp"

int main()
{
  Warlock richard("Richard", "the Titled");
  Warlock ricardo("Ricardo", "the Cursed");

  Dummy bob;
  Fwoosh* fwoosh = new Fwoosh();
  Fwoosh localFwoosh = Fwoosh();

  richard.learnSpell(fwoosh);
  ricardo.learnSpell(&localFwoosh);
  ricardo.learnSpell(NULL);

  richard.introduce();
  richard.launchSpell("Fwoosh", bob);
  richard.launchSpell("", bob);
  ricardo.introduce();
  ricardo.launchSpell("Fwoosh", bob);
  ricardo.launchSpell("", bob);

  richard.forgetSpell("Fwoosh");
  richard.launchSpell("Fwoosh", bob);
  ricardo.forgetSpell("Fwoosh");
  ricardo.launchSpell("Fwoosh", bob);

  // Breaks bcs maybe 42 doesn't know u gotta free ur own memory?
  //delete fwoosh;
}
