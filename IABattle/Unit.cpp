#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <vector>
#include "Unit.h"

unsigned int Unit::nbUnits = 0;

Unit::Unit(int levelTotal) : m_unitId(++nbUnits)
{
	std::vector<int> levelsIndex;
    int tabLevel[7] = { 0 };
    std::srand(std::time(0));
	
	m_unitPosition = new Point(100.0 * (std::rand() / RAND_MAX), 100.0 * (std::rand() / RAND_MAX));
	m_AICode = static_cast<AICode>(16 * (std::rand() / (RAND_MAX + 1))); //Generate the IACode randomly

	// Fill the vector for the random indexes
	for (int i = 0; i < 7; ++i)
		levelsIndex.push_back(i);
    for(int i = 0; i < 6; i++)
    {
		std::random_shuffle(levelsIndex.begin(), levelsIndex.end());
		tabLevel[levelsIndex[0]] = levelTotal * (std::rand() / (RAND_MAX + 1));
		levelTotal -= tabLevel[levelsIndex[0]];
		levelsIndex.erase(levelsIndex.begin());
    }
	tabLevel[levelsIndex[0]] = levelTotal;

	//Assign levels to capacities
    m_capacities[0] = new SpeedCapacity(tabLevel[0]);
    m_capacities[1] = new HealthCapacity(tabLevel[1]);
    m_capacities[2] = new ArmorCapacity(tabLevel[2]);
    m_capacities[3] = new RegenCapacity(tabLevel[3]);
    m_capacities[4] = new WeaponDamageCapacity(tabLevel[4]);
    m_capacities[5] = new WeaponRangeCapacity(tabLevel[5]);
    m_capacities[6] = new WeaponSpeedCapacity(tabLevel[6]);
}

Unit::Unit(AICode AICode
           , int speedLevel
           , int healthLevel
           , int armorLevel
           , int regenLevel
           , int weaponDamageLevel
           , int weaponRangeLevel
           , int weaponSpeedLevel
		   ) : m_unitId(++nbUnits), m_unitPosition(new Point(0, 0)), m_AICode(AICode)
{
    m_capacities[0] = new SpeedCapacity(speedLevel);
    m_capacities[1] = new HealthCapacity(healthLevel);
    m_capacities[2] = new ArmorCapacity(armorLevel);
    m_capacities[3] = new RegenCapacity(regenLevel);
    m_capacities[4] = new WeaponDamageCapacity(weaponDamageLevel);
    m_capacities[5] = new WeaponRangeCapacity(weaponRangeLevel);
    m_capacities[6] = new WeaponSpeedCapacity(weaponSpeedLevel);
}

Capacity& Unit::operator[](unsigned int i) const
{
	try
	{
		return dynamic_cast<Capacity&>(*m_capacities[i]);
	}
	catch (const std::out_of_range& oor)
	{
		std::cerr << "Out of range error: " << oor.what() << std::endl;
	}
}

int Unit::getLevel() const
{
    int levelTotal = 0;

    for(int i = 0; i < 7; i++)
    {
        levelTotal += m_capacities[i]->getLevel();
    }

    return levelTotal;
}

void Unit::refresh()
{
    HealthCapacity& health = this->getHealth();
    RegenCapacity& regen = this->getRegen();
    WeaponSpeedCapacity& weaponSpeed = this->getWeaponSpeed();

    //Life value can't be more than the max health
	health.setValue(std::max(health.getValue() + regen.getValue(), health.getValueMax()));

    if(weaponSpeed.getValue() > 0)
        weaponSpeed.setValue(weaponSpeed.getValue() - 1);
}

bool Unit::shoot()
{
    WeaponSpeedCapacity& weaponSpeed = this->getWeaponSpeed();
    if(weaponSpeed.getValue() == 0)
    {
        weaponSpeed.setValue(weaponSpeed.getValueMax());
        return true;
    }
    return false;
}

void Unit::takeDamage(float value)
{
    float newHealth = this->getHealth().getValue() - (value - this->getArmor().getValue());
    this->getHealth().setValue(newHealth);
}

bool Unit::isAlive() const
{
    return this->getHealth().getValue() > 0;
}
