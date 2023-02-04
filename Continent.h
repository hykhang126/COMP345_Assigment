#include <iostream>
#include <string>

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
        Continent(int pos, string name, int point, string color);
        ~Continent();
        void toString();
};