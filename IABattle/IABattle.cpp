// IABattle.cpp : Defines the entry point for the console application.
#include <iostream>
#include <algorithm>
#include <ctime>
#include <tuple>
#include <thread>
#include <chrono>
#include <map>
#include "Army.h"
#include "UnitAI.h"

void mainLoop();

int main(int argc, char* argv[]) {
	//Army a1(5, 20), a2(5, 20);
	//UnitAI ia;
	//int nbTours = 0;
	//std::vector<FighterWrapper> unitesCombat;

	//while (a1.size() > 0 && a2.size() > 0)
	//{
	//	nbTours++;
	//	if(nbTours % 100 == 0) {
	//		std::cout << "========== Tour " << nbTours << " ==========" << std::endl;
	//	}
	//	//Récupération des unités pour le tour
	//	unitesCombat.clear();
	//	for (auto & u : a1.getUnitList())
	//		unitesCombat.push_back(FighterWrapper(*u, a1, a2));
	//	for (auto & u : a2.getUnitList())
	//		unitesCombat.push_back(FighterWrapper(*u, a2, a1));
	//	
	//	while (unitesCombat.size() > 0)
	//	{
	//		std::random_shuffle(unitesCombat.begin(), unitesCombat.end());
	//		FighterWrapper fighter = unitesCombat.back();
	//		ia(fighter.m_fighter, fighter.m_allies, fighter.m_ennemies).execute();
	//		fighter.m_ennemies->purge();
	//		unitesCombat.pop_back();
	//	}
	//	for (auto & u : a1.getUnitList())
	//		u->refresh();
	//	for (auto & u : a2.getUnitList())
	//		u->refresh();
	//	std::this_thread::sleep_for(std::chrono::microseconds(1));
	//}
	//
	//std::cout << "Score Final:" << std::endl
	//	<< "Armee A: " << a1.size() << std::endl
	//	<< "Armee B: " << a2.size() << std::endl;

	mainLoop();

	return 0;
}

void mainLoop() {
	//INITIALISATION
	//int I = 5;
	//std::cout << "Entrez le nombre de combats : ";
	//std::cin >> I;
	//int N = 10;
	//std::cout << "Entrez le nombre d'armees : ";
	//std::cin >> N;
	//int X = 20;
	//std::cout << "Entrez le nombre d'unites des armees: ";
	//std::cin >> X;
	//int Y = 20;
	//std::cout << "Entrez le niveau global des unites: ";
	//std::cin >> Y;
	//int T = -1;
	//while(T == -1) {
	//	int temp;
	//	std::cout << "Entrez le score minimum a partir duquel sortir de la boucle de combats : ";
	//	std::cin >> temp;

	//	if(temp > (N - 1)*X) {
	//		std::cout << "Score minimum trop bas, entrez un nouveau score minimum : ";
	//	}
	//	else {
	//		T = temp;
	//	}
	//}

	//DEBUG
	int I = 5; //nombre d'itérations de combats
	int T = 2; //score seuil a partir duquel on sort de la boucle
	int N = 10; //nombre d'armées initiales
	int X = 1; //nombre d'unités
	int Y = 20; //niveau global initial

	std::vector<Army> armies;
	for(int i = 0; i < N; i++) {
		Army aTemp(X, Y);
		armies.push_back(aTemp);
	}

	//BOUCLE PRINCIPALE
	Army superiorArmy;

	int nbBoucles = 0;
	while(true) {
		nbBoucles++;
		std::vector<Army> tempArmies(armies);
		std::map<int, int> scoreForArmy;

		//Init du score
		for(int i = 0; i < N; i++) {
			scoreForArmy[Army(tempArmies.at(i)).getArmyId()] = 0;
		}

		//FAIRE SE COMBATTRE LES ARMEES ET GERER SCORE
		for(int i = 0; i < N; i++) {
			Army armyTempTempA = Army(tempArmies.at(i));

			for(int j = i + 1; j < N; j++) {
				Army armyTempA = Army(tempArmies.at(i));
				Army armyTempB = Army(tempArmies.at(j));

				/*********************************************************** COMBAT ! **********************************************************************************************/ 
				std::cout << std::endl;
				std::cout << "Armee " << armyTempA.getArmyId() << " contre Armee " << armyTempB.getArmyId() << std::endl;
				UnitAI ia;
				int nbTours = 0;
				std::vector<FighterWrapper> unitesCombat;

				while(armyTempA.size() > 0 && armyTempB.size() > 0) {
					nbTours++;
					std::cout << "========== Tour " << nbTours << " ==========" << std::endl;
					//Récupération des unités pour le tour
					unitesCombat.clear();
					for(auto & u : armyTempA.getUnitList())
						unitesCombat.push_back(FighterWrapper(*u, armyTempA, armyTempB));
					for(auto & u : armyTempB.getUnitList())
						unitesCombat.push_back(FighterWrapper(*u, armyTempB, armyTempA));

					while(unitesCombat.size() > 0) {
						std::random_shuffle(unitesCombat.begin(), unitesCombat.end());
						FighterWrapper fighter = unitesCombat.back();
						ia(fighter.m_fighter, fighter.m_allies, fighter.m_ennemies).execute();
						fighter.m_ennemies->purge();
						unitesCombat.pop_back();
					}
					for(auto & u : armyTempA.getUnitList())
						u->refresh();
					for(auto & u : armyTempB.getUnitList())
						u->refresh();
					//std::this_thread::sleep_for(std::chrono::microseconds(1));
				}

				std::cout << "Score Final:" << std::endl
				<< "Armee A: " << armyTempA.size() << std::endl
				<< "Armee B: " << armyTempB.size() << std::endl;

				/************************************************************************************************************************************************************/

				scoreForArmy[armyTempTempA.getArmyId()] += armyTempA.size();
				scoreForArmy[armyTempB.getArmyId()] += armyTempB.size();
			}
		}

		//CLASSER LES ARMEES PAR SCORE
		std::sort(tempArmies.begin(), tempArmies.end());

		//SI LE SCORE DE LA 1ERE EST > A T, BREAK
		if(scoreForArmy[tempArmies.at(0).getArmyId()] > T) {
			superiorArmy = tempArmies.at(0);
			//break;
		}

		//SINON GENERATION D'ARMEES

		//on garde les (N*0.1) meilleures armées
		std::vector<Army> newArmies;
		for(int i = 0; i < N * 0.1; i++) {
			newArmies.push_back(tempArmies.at(i));
		}

		//TODO: armées pas bien copiées (?), du coup ceux la plantent
		//On prend un croisement issu de chacune des (N*0.3) meilleures armées avec une autre prise aléatoirement
		//for(int i = 0; i < N * 0.3; i++) {
		//	newArmies.push_back(tempArmies.at(i) * tempArmies.at(std::rand() % N));
		//}

		//TODO: armées pas bien copiées (?), du coup ceux la plantent
		//on prend une mutation de chacune des (N*0.3) meilleures armées
		//for(int i = 0; i < N * 0.3; i++) {
		//	newArmies.push_back(tempArmies.at(i).mutate());
		//}

		//on génère (N*0.3) nouvelles armées aléatoirement
		while(newArmies.size() < N) {
			Army aTemp(X, Y);
			newArmies.push_back(aTemp);
		}

		armies = newArmies;

		std::cout << "Fin de la boucle : " << nbBoucles << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}

	//ARMEE SUPERIEURE
	superiorArmy.saveArmy();

	int a;
	std::cout << "FIN !" << std::endl;
	std::cin >> a;
}