// IABattle.cpp : Defines the entry point for the console application.
#include <iostream>
#include <algorithm>
#include "Army.h"
#include "UnitAI.h"

int main(int argc, char* argv[])
{
	Army a1(10, 10), a2(10, 10);
	Unit *u1, *u2;
	UnitAI ia;
	int nbTours = 1;

	while (a1.size() > 0 && a2.size() > 0)
	{
		std::cout << "========== Tour " << nbTours++ << " ==========" << std::endl;
		//Round of the first Army
		u1 = a1.getUnitList().at(std::rand() % a1.size());
		ia(*u1, a1, a2).execute();
		a2.purge();
		//Round of the second Army
		u2 = a2.getUnitList().at(std::rand() % a2.size());
		ia(*u2, a2, a1).execute();
		a1.purge();
	}
	
	std::cout << "Score Final:" << std::endl
		<< "Armée A: " << a1.size() << std::endl
		<< "Armée B: " << a2.size() << std::endl;

	return 0;
}

