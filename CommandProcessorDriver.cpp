#include "FileCommandProcessorAdapter.cpp"


int main()
{
    cout << "Please select input mode:" << endl;
    cout << "\"-console\" if entering manually." <<endl;
    cout << "\"-file\" if import list of commands by text file." <<endl;

    string mode = "";
    cin >> mode;
    if(mode == "-console")
    {
        string * currentState = new string("start");
        CommandProcessor * cp = new CommandProcessor();
        string input = "";
    
        while(input != "exit")
        {
            cp->GetCommand(currentState);
            cout << "Enter \"exit\" to finish or any key to continue." <<endl;
            cin >> input;
        }
        cout << "Show all commands before exiting: "<< endl;
        cp->ShowCommandList();
        cout << "Cleanning pointers: " << endl;
        delete cp;
    }
    else{
        if(mode == "-file")
        {
            string fileName;
            cout << "Please enter file name: " ;
            cin >> fileName; 
            try{
                string * cur = new string("start");
                CommandProcessor * cmdp = new FileCommandProcessorAdapter(fileName);
                cmdp->GetCommand(cur );
                cout << "Show all commands before exiting: "<< endl;
                cmdp->ShowCommandList();
                cout << "Cleanning pointers: " << endl;
                delete cmdp;
                }
            catch(invalid_argument& e)
            {
                cout << "Invalid file" <<endl;
            }
        }
        else{
            cout << "invalid command -> program terminated." <<endl;

        }
    }

    
    return 1;
}