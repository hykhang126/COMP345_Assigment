#include "GameEngine.h"
#include "GameEngine.cpp"

using namespace std;
// MAIN
int main(int argc, char const *argv[])
{
    Deck* deck = new Deck(20);
    Map* map = new Map();
    CommandProcessor *commandProcessor = new CommandProcessor();
    GameEngine *test = new GameEngine(commandProcessor, deck, map);
    vector<State*> stateList = test->getStateList();


    cout << "-----Welcome to Game Engine Driver----- \n";
    while (true)
    {
        cout << "1. Show names of all States\n";
        cout << "2. Show all transitions\n";
        cout << "3. Show the current State\n";
        cout << "4. Input a command\n";
        cout << "5. startupPhase\n";
        cout << "6. Tournament\n";
        cout << "99. End Demo\n";
        cout << "-----------------------------\n";

        int choice = 6;
        string input;
        cout << "Please make your choice: " << endl;
        // cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "-----------------------------\n";
            for (int i = 0; i < stateList.size(); i++)
                cout << *stateList[i]->getName() << endl;
            cout << "-----------------------------\n";
            break;
        case 2:
            cout << "-----------------------------\n";
            for (int i = 0; i < stateList.size(); i++)
                stateList[i]->showTransitions();
            cout << "-----------------------------\n";
            break;
        case 3:
            cout << "-----------------------------\n";
            cout << "Current State and its transitions:\n - ";
            test->getCurrentState()->showTransitions();
            cout << endl;
            break;
        case 4:
            cout << "\nPlease input your command: " << endl ;
            cin >> input;
            cout << "-----------------------------\n";
            cout << "Current State and its transitions:\n - ";
            test->getCurrentState()->showTransitions();
            cout << "Your command: " << input;
            cout << endl;
            test->isCommandValid(&input);
            break;
        case 5:
            test->startupPhase();
            break;
        case 6:
            test->Tournament();
            
        case 99:
            cout << "-----Thank you and goodbye!----- \n";
            return 0;
        default:
            break;
        }
    }

    delete test;
    return 0;
    
}
