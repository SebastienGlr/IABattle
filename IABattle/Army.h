#ifndef ARMY_H
#define ARMY_H

#include <vector>
#include "Unit.h"

class Army
{
public:
    Army(int, int);
    Army(const std::vector<Unit*>&);

    std::vector<Unit*> getUnitList() const { return m_unitList; }
    Unit& getUnit(int) const;
    int size() const { return this->m_unitList.size(); }
    Unit& getNearestUnit(const Point&) const;
    Unit& getFurthestUnit(const Point&) const;
    Unit& getLowestUnit(int) const;
    Unit& getHighestUnit(int) const;

    void purge();
private:
    std::vector<Unit*> m_unitList;
};

#endif // ARMY_H
