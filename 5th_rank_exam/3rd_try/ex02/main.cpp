#include "Warlock.hpp"
#include "Fwoosh.hpp"
#include "Dummy.hpp"
#include "BrickWall.hpp"
#include "Fireball.hpp"
#include "Polymorph.hpp"
#include "SpellBook.hpp"
#include "TargetGenerator.hpp"

int main()
{
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
	delete clone;

    // 7. Forget target type
	TargetGenerator t1;
	BrickWall wall1;
	t1.learnTargetType(&wall1);
	t1.forgetTargetType("Inconspicuous Red-brick Wall");
	ATarget* clone0 = t1.createTarget("Inconspicuous Red-brick Wall");
	if (!clone0)
		std::cout << "No such target found" << std::endl; // Expected
	delete clone0;

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
	delete clone1;
	delete clone2;

    // 14. Stress test repeated construction/destruction
	for (int i = 0; i < 10; ++i)
	{
		Warlock w8("Test", "the Tester");
		Fwoosh* f = new Fwoosh();
		w8.learnSpell(f);
		delete f;
	}
}
