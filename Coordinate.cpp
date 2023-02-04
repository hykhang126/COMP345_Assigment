#include "Coordinate.h"

int* Coordinate::getX()
{
    return x;
}

int* Coordinate::getY()
{
    return y;
}

Coordinate::Coordinate(int xx, int yy)
{
    x = new int(xx);
    y = new int(yy);
}

Coordinate::~Coordinate()
{
    delete x;
    delete y;
}

void Coordinate::toString()
{
    cout << "X: " << x << ", Y: " << y;
}