#ifndef POINT_H
#define POINT_H

namespace tour
{
class Point
{
public:
    Point(int x, int y);

    int X;
    int Y;

    Point& operator+(const Point& other)
    {
        X += other.X;
        Y += other.Y;

        return *this;
    }

    Point& operator+=(const Point &other)
    {
        *this = *this + other;

        return *this;
    }
};
}
#endif // POINT_H

