#include "Point.h"
#include <ostream>

Point::Point(float x, float y) : m_x(x), m_y(y)
{}

Point& Point::getNextPosWithSpeed(const Point& position, float speed) const
{
	// Return the Position we can go 
	double distance = Point::getDistance(*this, position);
	if (distance > speed)
	{
		float x = (speed * distance) * (position.m_x - this->m_x) + this->m_x;
		float y = (speed * distance) * (position.m_y - this->m_y) + this->m_y;
		return Point(x, y);
	}

	return Point(position);
}

Point& Point::operator=(const Point& p)
{
	if (this != &p)
	{
		this->m_x = p.m_x;
		this->m_y = p.m_y;
	}
	return *this;
}

std::ostream& operator<<(std::ostream &out, const Point& p)
{
	out << "(" << p.getX() << ", " << p.getY() << ")";
	return out;
}