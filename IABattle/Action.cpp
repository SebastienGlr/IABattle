#include "Action.h"
#include <iostream>

void ActionMove::execute()
{
	std::cout << "Unité " << m_from->getId() << " (Armée A) bouge en position " << m_position << std::endl;
	this->m_from->setPosition(*m_position);
}

void ActionShoot::execute()
{
	std::cout << "Unité " << m_from->getId() 
		<< " (Armée A) attaque Unité " << m_target->getId() 
		<< " (Armée B) qui n'a plus que" << m_target->getHealth().getValue() << " HP" 
		<< std::endl;
	this->m_from->shoot();
	this->m_target->takeDamage(this->m_from->getWeaponDamage().getValue());
}