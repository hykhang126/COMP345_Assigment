//
// Created by Eric on 3/14/2023.
//

#include "Command.h"
int main() {

    Command* com = new Command();

    com->SaveEffect(new string("hey"));
    com->SaveEffect(new string("nice"));
};