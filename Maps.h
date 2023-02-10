#include <map>
#include <list>
#include "Territory.cpp"

using namespace std;

class Maps{
    private :
        map<Territory*, list<Territory*>*> maps;

    public :
        void addTerritory(Territory * ter);
        void addEdge(Territory *ter, Territory *edg);
        int countTerritory();
        int countTotalEdge();
        void toString();
        Territory* getTerritoryByIndex(int i);
        ~Maps();
};