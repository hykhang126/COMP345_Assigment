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

Coordinate::Coordinate (const Coordinate& cor)
{
    this->x = cor.x;
    this->y = cor.y;
}

ostream& operator<< (ostream& output, Coordinate const &cor)
{
    output << "X: " << to_string(*cor.x) << ", Y: " << to_string(*cor.y);
    return output;
}

Coordinate& Coordinate::operator= (Coordinate const &cor){
    x = new int(*cor.x);
    y = new int(*cor.y);
    return *this;
}