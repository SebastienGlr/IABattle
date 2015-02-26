// IABattle.cpp : Defines the entry point for the console application.
#include <iostream>
#include <algorithm>
#include <ctime>
#include <tuple>
#include <thread>
#include <chrono>
#include "Army.h"
#include "UnitAI.h"

int main(int argc, char* argv[])
{
	Army a1(3, 2), a2(3, 100);
	UnitAI ia;
	int nbTours = 1;
	std::vector<std::tuple<Unit*, Army*, Army*> > unitesCombat;
	std::tuple<Unit*, Army*, Army*> fighter;

	while (a1.size() > 0 && a2.size() > 0)
	{
		std::cout << "========== Tour " << nbTours++ << " ==========" << std::endl;
		//Récupération des unités pour le tour
		unitesCombat.clear();
		for (auto u : a1.getUnitList())
			unitesCombat.push_back(std::make_tuple(u, &a1, &a2));
		for (auto u : a2.getUnitList())
			unitesCombat.push_back(std::make_tuple(u, &a2, &a1));
		
		while (unitesCombat.size() > 0)
		{
			std::random_shuffle(unitesCombat.begin(), unitesCombat.end());
			fighter = unitesCombat.back();
			ia(std::get<0>(fighter), std::get<1>(fighter), std::get<2>(fighter)).execute();
			std::get<2>(fighter)->purge();
			unitesCombat.pop_back();
		}
		for (auto u : a1.getUnitList())
			u->refresh();
		for (auto u : a2.getUnitList())
			u->refresh();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	
	std::cout << "Score Final:" << std::endl
		<< "Armee A: " << a1.size() << std::endl
		<< "Armee B: " << a2.size() << std::endl;

	return 0;
}

