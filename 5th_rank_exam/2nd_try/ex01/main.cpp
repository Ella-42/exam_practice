#include "Warlock.hpp"
#include "Dummy.hpp"
#include "Fwoosh.hpp"

#include <iostream>

void compileTest()
{
  //Warlock jerry;                          //Does not compile
  Warlock bob("Bob", "the magnificent");  //Compiles
  Warlock jim("Jim", "the nauseating");   //Compiles
  //bob = jim;                              //Does not compile
  //Warlock jack(jim);                      //Does not compile
}

int main()
{
  //Warlock const richard("Richard", "Mistress of Magma");
  //richard.introduce();
  //std::cout << richard.getName() << " - " << richard.getTitle() << std::endl;

  //Warlock* jack = new Warlock("Jack", "the Long");
  //jack->introduce();
  //jack->setTitle("the Mighty");
  //jack->introduce();

  //compileTest();

  //delete jack;

  //Warlock richard("Richard", "the Titled");

  //Dummy bob;
  //Fwoosh* fwoosh = new Fwoosh();

  //richard.learnSpell(fwoosh);

  //richard.introduce();
  //richard.launchSpell("Fwoosh", bob);

  //richard.forgetSpell("Fwoosh");
  //richard.launchSpell("Fwoosh", bob);

    //Warlock richard("Richard", "the Titled");
    //richard.introduce();

    //Dummy dummy;
    //Fwoosh fwoosh;

    // Learn spell
    //richard.learnSpell(&fwoosh);

    // Launch known spell
    //richard.launchSpell("Fwoosh", dummy);

    // Launch unknown spell - should do nothing, no crash
    //richard.launchSpell("Fireball", dummy);

    // Forget spell and try launch again - no output expected
    //richard.forgetSpell("Fwoosh");
    //richard.launchSpell("Fwoosh", dummy);

    // Learn again, introduce title change
    //richard.learnSpell(&fwoosh);
    //richard.setTitle("the Brave");
    //richard.introduce();

    //Fwoosh original;
    //ASpell* clone = original.clone();

    //Dummy originalDummy;
    //ATarget* dummyClone = originalDummy.clone();

    //std::cout << "Original spell: " << original.getName() << "\n";
    //std::cout << "Clone spell: " << clone->getName() << "\n";

    //std::cout << "Original target: " << originalDummy.getType() << "\n";
    //std::cout << "Clone target: " << dummyClone->getType() << "\n";

    //delete clone;
    //delete dummyClone;

    // Local stack spell + clone
    Fwoosh f;
    ASpell* fClone = f.clone();

    // Caller owns clone, must delete
    std::cout << "Original spell: " << f.getName() << "\n";
    std::cout << "Clone spell: " << fClone->getName() << "\n";
    delete fClone;

    // Local stack target + clone
    Dummy d;
    ATarget* dClone = d.clone();

    std::cout << "Original target: " << d.getType() << "\n";
    std::cout << "Clone target: " << dClone->getType() << "\n";
    delete dClone;

    // Mix clone and learn
    Warlock w("Richard", "the Great");

    ASpell* dynamicFwoosh = new Fwoosh();
    w.learnSpell(dynamicFwoosh->clone()); // you clone, you store
    delete dynamicFwoosh; // caller deletes their new

    Dummy dummy;
    w.launchSpell("Fwoosh", dummy); // warlock uses internal clone
}
