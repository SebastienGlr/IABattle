#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <vector>
#include "Unit.h"

unsigned int Unit::nbUnits = 0;

Unit::Unit(int levelTotal) : m_unitId(++nbUnits)
{
	std::random_device rd;
	std::default_random_engine e1(rd());
	std::uniform_int_distribution<> uniform_dist(0.f, 100.f);
	
	m_unitPosition = Point(uniform_dist(e1), uniform_dist(e1));

	uniform_dist = std::uniform_int_distribution<>(0, 15);
	m_AICode = static_cast<AICode>(uniform_dist(e1)); //Generate the IACode randomly
	
	m_capacities[0] = new SpeedCapacity(0);
	m_capacities[1] = new HealthCapacity(0);
	m_capacities[2] = new ArmorCapacity(0);
	m_capacities[3] = new RegenCapacity(0);
	m_capacities[4] = new WeaponDamageCapacity(0);
	m_capacities[5] = new WeaponRangeCapacity(0);
	m_capacities[6] = new WeaponSpeedCapacity(0);
	// Fill the vector for the random indexes
	uniform_dist = std::uniform_int_distribution<>(0, 6);
	for (int i = 0; i < levelTotal; ++i)
		m_capacities[uniform_dist(e1)]->upgrade();
}

Unit::Unit(AICode AICode
           , int speedLevel
           , int healthLevel
           , int armorLevel
           , int regenLevel
           , int weaponDamageLevel
           , int weaponRangeLevel
           , int weaponSpeedLevel
		   ) : m_unitId(++nbUnits), m_AICode(AICode)
{
	std::random_device rd;
	std::default_random_engine e1(rd());
	std::uniform_int_distribution<> uniform_dist(0.f, 100.f);

	Point m_unitPosition(uniform_dist(e1), uniform_dist(e1));

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
    this->operator[](1).setValue(newHealth);
}

bool Unit::isAlive() const
{
    return this->getHealth().getValue() > 0;
}
