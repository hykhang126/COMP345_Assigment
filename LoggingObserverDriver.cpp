//
// Created by Eric on 3/14/2023.
//

#include "CommandProcessing.h"
#include "GameEngine.h"
#include "Orders.h"-

int main() {

    // Creating observer and subjects
    LogObserver *gameLogObserver = new LogObserver;

    Command* com = new Command(new string("test command"));
    CommandProcessor* comProc = new CommandProcessor();
    GameEngine* gameEngine = new GameEngine();
    OrdersList* ordersList = new OrdersList();
    Deploy* deployOrder = new Deploy();

    // Attaching all subjects with observer
    com->attach(gameLogObserver);
    comProc->attach(gameLogObserver);
    gameEngine->attach(gameLogObserver);
    ordersList->attach(gameLogObserver);
    deployOrder->attach(gameLogObserver);

    // Performing state changes. Logs can be found in ./cmake-build-debug/gameLog.txt
    ordersList->addOrder(deployOrder);
    ordersList->getList().back()->execute();
    com->SaveEffect(new string("test effect"));
    comProc->SaveCommand(com);
    gameEngine->isCommandValid(new  string("loadMap"));


    // Detaching all subjects from observer
    com->detach(gameLogObserver);
    comProc->detach(gameLogObserver);
    gameEngine->detach(gameLogObserver);
    ordersList->detach(gameLogObserver);
    deployOrder->detach(gameLogObserver);

    // Deleting pointers
    delete(gameLogObserver);
    gameLogObserver = nullptr;

    // Individual orders and commands deleted when deleting ordersList and comProc, no need to delete them twice
    delete(comProc);
    delete gameEngine;
    delete ordersList;

    com = nullptr;
    comProc = nullptr;
    gameEngine = nullptr;
    ordersList = nullptr;
    deployOrder = nullptr;
};