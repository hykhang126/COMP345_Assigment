#include <iostream>

using namespace std;

class Coordinate{
    private:
        int* x;
        int* y;
    public: 
        int* getX();
        int* getY();
        Coordinate(int* xx, int* yy);
        ~Coordinate();
        string toString();
};