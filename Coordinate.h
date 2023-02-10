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
        Coordinate (const Coordinate& cor);
        friend ostream& operator<< (ostream& output, Coordinate const &cor);
        Coordinate& operator= (Coordinate const &cor);
};