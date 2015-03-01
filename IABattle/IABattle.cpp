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
	Army a1(5, 20), a2(5, 20);
	UnitAI ia;
	int nbTours = 1;
	std::vector<FighterWrapper> unitesCombat;

	while (a1.size() > 0 && a2.size() > 0)
	{
		std::cout << "========== Tour " << nbTours++ << " ==========" << std::endl;
		//Récupération des unités pour le tour
		unitesCombat.clear();
		for (auto & u : a1.getUnitList())
			unitesCombat.push_back(FighterWrapper(*u, a1, a2));
		for (auto & u : a2.getUnitList())
			unitesCombat.push_back(FighterWrapper(*u, a2, a1));
		
		while (unitesCombat.size() > 0)
		{
			std::random_shuffle(unitesCombat.begin(), unitesCombat.end());
			FighterWrapper fighter = unitesCombat.back();
			ia(fighter.m_fighter, fighter.m_allies, fighter.m_ennemies).execute();
			fighter.m_ennemies->purge();
			unitesCombat.pop_back();
		}
		for (auto & u : a1.getUnitList())
			u->refresh();
		for (auto & u : a2.getUnitList())
			u->refresh();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	
	std::cout << "Score Final:" << std::endl
		<< "Armee A: " << a1.size() << std::endl
		<< "Armee B: " << a2.size() << std::endl;

	return 0;
}

