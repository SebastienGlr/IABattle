#ifndef POINT_H
#define POINT_H
#include <math.h>

class Point
{
    public:
        Point(float, float);
		Point& operator=(const Point&);

        float getX() const { return m_x; }
        float getY() const { return m_y; }
        static double getDistance(const Point& p1, const Point& p2)
        {
			return sqrt(static_cast<double>((p1.m_x - p2.m_x)*(p1.m_x - p2.m_x) + (p1.m_y - p2.m_y)*(p1.m_y - p2.m_y)));
        }
		Point& getNextPosWithSpeed(const Point&, float) const;
    private:
        float m_x;
        float m_y;
};

#endif // POINT_H
