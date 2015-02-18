#include "SpeedCapacity.h"

SpeedCapacity::SpeedCapacity(int level) : Capacity(level)
{
    computeValue();
}

void SpeedCapacity::computeValue()
{
    this->m_value = 1 + this->m_level;
}
