#include "GameEngine.cpp"

// MAIN
int main(int argc, char const *argv[])
{
    GameEngine *test = new GameEngine();
    vector<State*> stateList;
    stateList = test->getStateList();


    delete test;
    return 0;
}
