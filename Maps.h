#include <map>
#include <list>
#include "Territory.h"

using namespace std;

class Maps{
    private :
        map<Territory*, list<Territory*>> maps;

    public :
        void addTerritory(Territory * ter);
        void addEdge(Territory *ter, Territory *edg);
        int countTerritory();
        int countEdge();
        void toString();
        Maps();
        ~Maps();
    
};