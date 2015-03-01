#include "Army.h"
#include <fstream>

Army::Army(int nbUnit, int levelUnit)
{
    for(int i = 0; i < nbUnit; i++)
        this->m_unitList.push_back(new Unit(levelUnit));
}

Army::Army(const std::vector<Unit*>& unitList) : m_unitList(unitList)
{
}

Unit& Army::getUnit(int idUnit)
{
    for(auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
        if((*it)->getId() == idUnit)
           return **it;

    throw std::runtime_error("ID not in list.");
}

Unit& Army::getNearestUnit(const Point& p) const
{
    Unit *u = this->m_unitList.front();
    double dist = Point::getDistance(u->getPosition(), p);

	for (auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
	{
		double tmp;
		if ((tmp = Point::getDistance((*it)->getPosition(), p)) < dist)
		{
			dist = tmp;
			u = *it;
		}
	}
    return *u;
}

Unit& Army::getFurthestUnit(const Point& p) const
{
    Unit * u = this->m_unitList.front();
    double dist = Point::getDistance(u->getPosition(), p);

	for (auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
	{
		double tmp;
		if ((tmp = Point::getDistance((*it)->getPosition(), p)) > dist)
		{
			dist = tmp;
			u = *it;
		}
	}
    return *u;
}

Unit& Army::getLowestUnit(int capacityIndex) const
{
    Unit * u = this->m_unitList.front();
	int level = u->operator[](capacityIndex).getLevel();

	for (auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
	{
		double tmp;
		if ((tmp = (*it)->operator[](capacityIndex).getLevel()) < level)
		{
			level = tmp;
			u = *it;
		}
	}
    return *u;
}

Unit& Army::getHighestUnit(int capacityIndex) const
{
    Unit * u = this->m_unitList.front();
    int level = u->operator[](capacityIndex).getLevel();

	for (auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
	{
		double tmp;
		if ((tmp = (*it)->operator[](capacityIndex).getLevel()) > level)
		{
			level = tmp;
			u = *it;
		}
	}
    return *u;
}

void Army::purge()
{
	for (auto it = this->m_unitList.begin(); it != this->m_unitList.end();)
	{
		if (!(*it)->isAlive())
			it = m_unitList.erase(it);
		else
			it++;
	}
}

