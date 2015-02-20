// IABattle.cpp : Defines the entry point for the console application.
#include <iostream>
#include <algorithm>
#include <ctime>
#include <tuple>
#include "Army.h"
#include "UnitAI.h"

int main(int argc, char* argv[])
{
	Army *a1 = new Army(10, 10), *a2 = new Army(10, 10);
	std::tuple<Unit*, Army*, Army*> fighter;
	UnitAI ia;
	int nbTours = 1;
	std::vector<std::tuple<Unit*, Army*, Army*> > unitesCombat;

	while (a1->size() > 0 && a2->size() > 0)
	{
		std::cout << "========== Tour " << nbTours++ << " ==========" << std::endl;
		//Récupération des unités pour le tour
		unitesCombat.clear();
		for (auto && u : a1->getUnitList())
			unitesCombat.push_back(std::make_tuple(u, a1, a2));
		for (auto && u : a2->getUnitList())
			unitesCombat.push_back(std::make_tuple(u, a2, a1));
		
		while (unitesCombat.size() > 0)
		{
			std::random_shuffle(unitesCombat.begin(), unitesCombat.end());

			fighter = unitesCombat.back();
			ia(*std::get<0>(fighter), *std::get<1>(fighter), *std::get<2>(fighter)).execute();
			std::get<2>(fighter)->purge();
			unitesCombat.pop_back();
		}
	}
	
	std::cout << "Score Final:" << std::endl
		<< "Armée A: " << a1->size() << std::endl
		<< "Armée B: " << a2->size() << std::endl;

	return 0;
}

