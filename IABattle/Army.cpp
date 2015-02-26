#include "Army.h"

Army::Army(int nbUnit, int levelUnit)
{
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
    Unit *u = this->m_unitList.front();
    double dist = Point::getDistance(u->getPosition(), p), tmp;

    for(auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
        if((tmp = Point::getDistance((*it)->getPosition(), p)) < dist)
            dist = tmp;

    return *u;
}

Unit& Army::getFurthestUnit(const Point& p) const
{
    Unit *u = this->m_unitList.front();
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
    Unit *u = this->m_unitList.front();
	int level = u->operator[](capacityIndex).getLevel(), tmp;

    for(auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
		if ((tmp = (*it)->operator[](capacityIndex).getLevel()) < level)
        {
            level = tmp;
            u = *it;
        }
    return *u;
}

Unit& Army::getHighestUnit(int capacityIndex) const
{
    Unit *u = this->m_unitList.front();
    int level = u->operator[](capacityIndex).getLevel(), tmp;

    for(auto it = this->m_unitList.begin(); it != this->m_unitList.end(); ++it)
        if((tmp = (*it)->operator[](capacityIndex).getLevel()) > level)
        {
            level = tmp;
            u = *it;
        }
    return *u;
}

void Army::purge()
{
	for (auto it = this->m_unitList.begin(); it != this->m_unitList.end();)
	{
		if (!(*it)->isAlive())
		{
			delete *it;
			*it = nullptr;
			it = m_unitList.erase(it);
		}
		else
			it++;
	}
}

