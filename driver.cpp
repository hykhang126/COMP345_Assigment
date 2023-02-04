#include "Territory.h"

int main()
{
    Territory ter1(new Player(), new int(41), new int(1), new string("new mexico"), new Continent(1,"Asian",4, "red"), new Coordinate(222,333) );
    ter1.toString();
}