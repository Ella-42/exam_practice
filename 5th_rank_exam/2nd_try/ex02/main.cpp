#include "Warlock.hpp"
#include "Dummy.hpp"
#include "Fwoosh.hpp"
#include "BrickWall.hpp"
#include "Polymorph.hpp"
#include "TargetGenerator.hpp"
#include "Fireball.hpp"

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
    //Fwoosh f;
    //ASpell* fClone = f.clone();

    // Caller owns clone, must delete
    //std::cout << "Original spell: " << f.getName() << "\n";
    //std::cout << "Clone spell: " << fClone->getName() << "\n";
    //delete fClone;

    // Local stack target + clone
    //Dummy d;
    //ATarget* dClone = d.clone();

    //std::cout << "Original target: " << d.getType() << "\n";
    //std::cout << "Clone target: " << dClone->getType() << "\n";
    //delete dClone;

    // Mix clone and learn
    //Warlock w("Richard", "the Great");

    //ASpell* dynamicFwoosh = new Fwoosh();
    //w.learnSpell(dynamicFwoosh->clone()); // you clone, you store
    //delete dynamicFwoosh; // caller deletes their new

    //Dummy dummy;
    //w.launchSpell("Fwoosh", dummy); // warlock uses internal clone

    //Warlock richard("Richard", "foo");
    //richard.setTitle("Hello, I'm Richard the Warlock!");
    //BrickWall model1;

    //Polymorph* polymorph = new Polymorph();
    //TargetGenerator tarGen;

    //tarGen.learnTargetType(&model1);
    //richard.learnSpell(polymorph);

    //Fireball* fireball = new Fireball();

    //richard.learnSpell(fireball);

    //ATarget* wall = tarGen.createTarget("Inconspicuous Red-brick Wall");

    //richard.introduce();
    //richard.launchSpell("Polymorph", *wall);
    //richard.launchSpell("Fireball", *wall);

    // 1. Warlock constructor & destructor
	Warlock w("Morty", "the Confused");
    // Expect: Morty: This looks like another boring day.\n ... My job here is done!\n

    // 2. setTitle() & introduce()
	Warlock w1("Rick", "the Mad");
	w1.setTitle("the Slightly Less Mad");
	w1.introduce(); // Rick: I am Rick, the Slightly Less Mad!

    // 3. Learn spell, forget spell
	Warlock w2("Rincewind", "the Runner");
	Fwoosh* f = new Fwoosh();
	w2.learnSpell(f);
	w2.launchSpell("Fwoosh", Dummy()); // Dummy has been fwooshed!
	w2.forgetSpell("Fwoosh");
	w2.launchSpell("Fwoosh", Dummy()); // no effect
	delete f;

    // 4. Learn same spell twice
	Warlock w3("Sabrina", "the Witch");
	Fwoosh* f1 = new Fwoosh();
	Fwoosh* f2 = new Fwoosh();
	w3.learnSpell(f1);
	w3.learnSpell(f2);
	delete f1;
	delete f2;

    // 5. Launch non-existent spell
	Warlock w4("Merlin", "the OG");
	w4.launchSpell("Firestorm", Dummy()); // no effect

    // 6. Learn and create target
	TargetGenerator t;
	BrickWall wall;
	t.learnTargetType(&wall);
	ATarget* clone = t.createTarget("Inconspicuous Red-brick Wall");
	std::cout << clone->getType() << std::endl; // Inconspicuous Red-brick Wall

    // 7. Forget target type
	TargetGenerator t1;
	BrickWall wall1;
	t1.learnTargetType(&wall1);
	t1.forgetTargetType("Inconspicuous Red-brick Wall");
	ATarget* clone0 = t1.createTarget("Inconspicuous Red-brick Wall");
	if (!clone0)
		std::cout << "No such target found" << std::endl; // Expected

    // 8. Spells clone properly
	Warlock w5("Yennefer", "of Vengerberg");
	Fireball* fb = new Fireball();
	w.learnSpell(fb);
	delete fb;
	BrickWall b;
	w5.launchSpell("Fireball", b); // burnt to a crisp

    // 9. Memory leak check with valgrind is manual, so no code here.

    // 10. Learn NULL spell (should be safe)
	Warlock w6("Testy", "McTestface");
	w6.learnSpell(NULL);

    // 11. Forget non-existent spell
	Warlock w7("Testy", "McTestface");
	w7.forgetSpell("");
	w7.forgetSpell("DefinitelyNotASpell");

    // 12. Launch spell with NULL target - don't do this in real runs (undefined behavior)
    // w.launchSpell("Fwoosh", *(ATarget*)NULL);

    // 13. Full integration test
	Warlock w8("Harry", "the Lame");
	TargetGenerator t2;
	BrickWall bw;
	Dummy d;

	Fwoosh* f3 = new Fwoosh();
	Polymorph* p = new Polymorph();
	Fireball* fb1 = new Fireball();

	t2.learnTargetType(&bw);
	t2.learnTargetType(&d);

	w8.learnSpell(f3);
	w8.learnSpell(p);
	w8.learnSpell(fb1);

	ATarget* clone1 = t2.createTarget("Inconspicuous Red-brick Wall");
	ATarget* clone2 = t2.createTarget("Target Practice Dummy");

	w8.launchSpell("Fwoosh", *clone2);       // Dummy has been fwooshed!
	w8.launchSpell("Polymorph", *clone1);    // turned into a critter!
	w8.launchSpell("Fireball", *clone1);     // burnt to a crisp!

	delete f3;
	delete p;
	delete fb1;

    // 14. Stress test repeated construction/destruction
	for (int i = 0; i < 10; ++i)
	{
		Warlock w8("Test", "the Tester");
		Fwoosh* f = new Fwoosh();
		w8.learnSpell(f);
		delete f;
	}
}
