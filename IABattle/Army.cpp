#include "Army.h"

#include <fstream>

Army::Army(int nbUnit, int levelUnit) {
	for(int i = 0; i < nbUnit; ++i)
		this->m_unitList.push_back(new Unit(levelUnit));
}

Army::Army(const std::vector<Unit*>& unitList) : m_unitList(unitList) {
}

Unit& Army::getUnit(int idUnit) const {
	for(auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
		if((*it)->getId() == idUnit)
			return *(*it);

	throw std::string("Unit not in list.");
}

Unit& Army::getNearestUnit(const Point& p) const {
	Unit *u = this->m_unitList.front();
	double dist = Point::getDistance(u->getPosition(), p), tmp;

	for(auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
		if((tmp = Point::getDistance((*it)->getPosition(), p)) < dist)
			dist = tmp;

	return *u;
}

Unit& Army::getFurthestUnit(const Point& p) const {
	Unit *u = this->m_unitList.front();
	double dist = Point::getDistance(u->getPosition(), p), tmp;

	for(auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
		if((tmp = Point::getDistance((*it)->getPosition(), p)) > dist) {
			dist = tmp;
			u = *it;
		}
	return *u;
}

Unit& Army::getLowestUnit(int capacityIndex) const {
	Unit *u = this->m_unitList.front();
	int level = u->operator[](capacityIndex).getLevel(), tmp;

	for(auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
		if((tmp = (*it)->operator[](capacityIndex).getLevel()) < level) {
			level = tmp;
			u = *it;
		}
	return *u;
}

Unit& Army::getHighestUnit(int capacityIndex) const {
	Unit *u = this->m_unitList.front();
	int level = u->operator[](capacityIndex).getLevel(), tmp;

	for(auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
		if((tmp = (*it)->operator[](capacityIndex).getLevel()) > level) {
			level = tmp;
			u = *it;
		}
	return *u;
}

void Army::purge() {
	for(auto it = this->m_unitList.begin(); it != this->m_unitList.end();) {
		if(!(*it)->isAlive()) {
			delete *it;
			*it = nullptr;
			it = m_unitList.erase(it);
		}
		else
			it++;
	}
}

int  Army::getGlobalLevel() const {
	int globalLevel = 0;

	for each (Unit* unit in m_unitList) {
		globalLevel += unit->getLevel();
	}

	return globalLevel;
}

void  Army::saveArmy() const {
	std::string fileName = "army_" + std::to_string(size()) + "_" + std::to_string(getGlobalLevel()) + ".save";

	std::ofstream armySaveFile(fileName/*, std::ios::out | std::ios::trunc*/);

	if(!armySaveFile) {
		throw 1;
	}
	else {
		for each (Unit* unit in m_unitList) {
			armySaveFile << unit->getSpeed().getLevel() << unit->getHealth().getLevel() << unit->getArmor().getLevel() << unit->getRegen().getLevel() << unit->getWeaponDamage().getLevel() << unit->getWeaponRange().getLevel() << unit->getWeaponSpeed().getLevel() << unit->getAICode() << std::endl;
		}
		armySaveFile.close();
	}
}

