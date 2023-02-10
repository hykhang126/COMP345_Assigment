#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Continent{
    private:
        int* position;
        string* name;
        int* point;
        string* color;

    public:
        int* getPosition();
        string* getName();
        int* getPoint();
        string* getColor();
        Continent(int* pos, string* name, int* point, string* color);
        ~Continent();
        Continent(const Continent &src);
        string toString();
        Continent& operator= (const Continent &src);
        friend ostream& operator<< (ostream &os, const Continent &cont);
};