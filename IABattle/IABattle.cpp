// IABattle.cpp : Defines the entry point for the console application.
#include <iostream>
#include <algorithm>
#include <ctime>
#include "Army.h"
#include "UnitAI.h"

int main(int argc, char* argv[])
{
	Army a1(10, 10), a2(10, 10);
	Unit *u1, *u2;
	UnitAI ia;
	int nbTours = 1;
	srand(time(NULL));

	while (a1.size() > 0 && a2.size() > 0)
	{
		std::cout << "========== Tour " << nbTours++ << " ==========" << std::endl;
		//Round of the first Army
		std::random_shuffle(a1.getUnitList().begin(), a1.getUnitList().end());
		u1 = a1.getUnitList().front();
		ia(*u1, a1, a2).execute();
		a2.purge();
		//Round of the second Army
		std::random_shuffle(a2.getUnitList().begin(), a2.getUnitList().end());
		u2 = a2.getUnitList().front();
		ia(*u2, a2, a1).execute();
		a1.purge();
	}
	
	std::cout << "Score Final:" << std::endl
		<< "Armée A: " << a1.size() << std::endl
		<< "Armée B: " << a2.size() << std::endl;

	return 0;
}

