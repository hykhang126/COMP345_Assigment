#include "CommandProcessor.cpp"


int main()
{
    // cout << "Please input command:" << endl;
    // cout << "(include \"-console\" if entering manually.)" <<endl;
    // cout << "(include \"-file <filename>\" if import list of commands by text file.)" <<endl;

    // string mode = "";
    // cin >> mode;
    // if(mode == "-console")
    // {
    //     cout << "Please enter commands' name seperated by new line: " <<endl;
    //     cout << "Finish entering by state \"done\"" << endl;
    //     string command = "";
    //     while(command != "done")
    //     {
    //         Command * com = new Command(new string(command));
    //         this->SaveCommand(com);
    //     }
    // }
    // else{
    //     std::vector<std::string> words;
    //     std::istringstream iss(mode);
    //     std::string word;
    //     while (std::getline(iss, word, ' ')) {
    //         words.push_back(word);
    //     }

    //     if(words[0] == "-file")
    //     {
    //         try{
    //             string line;
    //             ifstream reader;
    //             reader.open(words[1]);
    //             if(reader.is_open())
    //             {
    //                 while(getline(reader,line)){
    //                     Command * com = new Command(new string(line));
    //                     this->SaveCommand(com);
    //                 }
    //             }
    //             reader.close();
    //             cout << "++++++++++++Load file into command list successfully" << endl;
    //             }
    //         catch(invalid_argument& e)
    //         {
    //             cout << "Invalid file" <<endl;
    //         }
    //     }
    //     else{
    //         cout << "invalid command -> program terminated." <<endl;

    //     }
    // }

    string * currentState = new string("start");
    CommandProcessor * cp = new CommandProcessor();
    cp->GetCommand(currentState);
    return 1;
}