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

void Continent::toString()
{
    cout << "position: " << getPosition() << ", Name: " << getName() << ", point: " << getPoint() << ", color: " << getColor();
}

Continent::Continent(int pos, string nm, int pts, string clr){
    position = new int(pos);
    name = new string(nm);
    point = new int(pts);
    color = new string(clr);
}

Continent::~Continent()
{
    delete position;
    delete name;
    delete point;
    delete color;
}