#include <list>
#include <vector>
#include "Territory.h"

using namespace std;

class Player{
    private :
        Hand* _hand;
        vector<Territory*>* tCollection;
    public :
        list<Territory> toDefend();
        list<Territory> toAttack();
        void issueOrder();
};