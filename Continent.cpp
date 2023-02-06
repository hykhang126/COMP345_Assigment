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

Continent::Continent(const Continent &src)
{
    position = new int(*src.position);
    name = new string(*src.name);
    point = new int(*src.point);
    color = new string(*src.color);
}

Continent& Continent::operator= (const Continent &src)
{
    position = new int(*src.position);
    name = new string(*src.name);
    point = new int(*src.point);
    color = new string(*src.color);
}

ostream& operator<< (ostream &os, const Continent &cont)
{
    os << "position: " << cont.position << ", Name: " << cont.name <<  ", point: " << cont.point << ", color: " << cont.color;
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