#include "Army.h"

Army::Army(int nbUnit, int levelUnit)
{
    this->m_unitList = std::vector<Unit*>(nbUnit);
    for(int i = 0; i < nbUnit; ++i)
        this->m_unitList.push_back(new Unit(levelUnit));
}

Army::Army(const std::vector<Unit*>& unitList) : m_unitList(unitList)
{
}

Unit& Army::getUnit(int idUnit) const
{
    for(auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
        if((*it)->getId() == idUnit)
           return *(*it);

    throw std::string("Unit not in list.");
}

Unit& Army::getNearestUnit(const Point& p) const
{
    Unit *u = this->m_unitList[0];
    double dist = Point::getDistance(u->getPosition(), p), tmp;

    for(auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
        if((tmp = Point::getDistance((*it)->getPosition(), p)) < dist)
            dist = tmp;

    return *u;
}

Unit& Army::getFurthestUnit(const Point& p) const
{
    Unit *u = this->m_unitList[0];
    double dist = Point::getDistance(u->getPosition(), p), tmp;

    for(auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
        if((tmp = Point::getDistance((*it)->getPosition(), p)) > dist)
        {
            dist = tmp;
            u = *it;
        }
    return *u;
}

Unit& Army::getLowestUnit(int capacityIndex) const
{
    Unit *u = this->m_unitList[0];
    int level = u[capacityIndex].getLevel(), tmp;

    for(auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
        if((tmp = (*it)[capacityIndex].getLevel()) < level)
        {
            level = tmp;
            u = *it;
        }
    return *u;
}

Unit& Army::getHighestUnit(int capacityIndex) const
{
    Unit *u = this->m_unitList[0];
    int level = u[capacityIndex].getLevel(), tmp;

    for(auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
        if((tmp = (*it)[capacityIndex].getLevel()) > level)
        {
            level = tmp;
            u = *it;
        }
    return *u;
}

void Army::purge()
{
	for (auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
	{
		if (!(*it)->isAlive())
			m_unitList.erase(it);
	}
}

