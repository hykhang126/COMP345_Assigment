#include "GameEngine.cpp"

// MAIN
int main(int argc, char const *argv[])
{
    GameEngine *test = new GameEngine();
    vector<State*> stateList;
    stateList = test->getStateList();

    for (int i = 0; i < stateList.size(); i++)
    {
        // cout << *stateList[i]->getName() << endl;
        stateList[i]->showTransitions();
    }

    delete test;
    return 0;
}
