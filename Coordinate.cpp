#include "Coordinate.h"

int* Coordinate::getX()
{
    return x;
}

int* Coordinate::getY()
{
    return y;
}

Coordinate::Coordinate(int* xx, int* yy)
{
    x = xx;
    y = yy;
}

Coordinate::~Coordinate()
{
    delete x;
    delete y;
    cout<<"delete";
}

string Coordinate::toString()
{
    return "X: " + to_string(*x) + ", Y: " + to_string(*y);
}