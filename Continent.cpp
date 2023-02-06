#include "Continent.h"

int* Continent::getPosition()
{
    return position;
}

string* Continent::getName()
{
    return name;
}

int* Continent::getPoint()
{
    return point;
}

string* Continent::getColor()
{
    return color;
}

string Continent::toString()
{
    return "position: " + to_string(*getPosition()) + ", Name: " + *getName() + ", point: " + to_string(*getPoint()) + ", color: " + *getColor();
}

Continent::Continent(int* pos, string* nm, int* pts, string* clr){
    position = pos;
    name = nm;
    point = pts;
    color = clr;
}

Continent::~Continent()
{
    delete position;
    delete name;
    delete point;
    delete color;
    cout << "delete";
}