#include "CommandProcessing.cpp"


int main()
{
    cout << "Please select input mode:" << endl << endl;
    cout << "\"-console\" if entering manually." <<endl;
    cout << "\"-file\" if import list of commands by text file." <<endl;
    cout << "Enter your choice: ";

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
        cout << "---------------- Exiting --------------------------" <<endl;
        cout << "Show all commands before exiting: "<< endl;
        cp->ShowCommandList();
         cout << "--------------------------------------"<<endl;
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
                cout << "---------------- Exiting --------------------------" <<endl;
                cout << "Show all commands before exiting: "<< endl;
                cmdp->ShowCommandList();
                cout << "--------------------------------------"<<endl;
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
    int temp;
    cin >> temp;
    return 1;
}