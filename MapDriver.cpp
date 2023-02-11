#include "Map.cpp"


int main()
{   
    cout << "Choose the action:"<<endl;
    cout << "1: load map from file" << endl;
    cout << "2: show all continents" << endl;
    cout << "3: show all countries" << endl;
    cout << "4: show countries and its border" << endl;
    cout << "5: validate map" << endl;
    cout << "99: exit" << endl;
    int input;
    cout << "Enter your choice: ";
    cin >> input;
    Map* map;
    MapLoader loader;

    while(input != 99 )
    {
        if(input == 1)
        {
            cout << endl << endl <<endl;
            cout << "Enter file's name (ex:) from which map is loaded: ";
            string filename;
            cin >> filename;
            map = loader.loadMapFromFile(filename);
        }
        if(input == 2)
        {
            cout << endl << endl <<endl;
            map->showAllCoutry();
        }
        if(input == 3)
        {
            cout << endl << endl <<endl;
            map->showAllBorder();
        }
        if(input == 4)
        {
            cout << endl << endl <<endl;
            map->showAllContinent();
        }
        if(input == 5)
        {
            cout << endl << endl <<endl;
            map->validate();
        }

        cout <<endl <<endl <<endl<< "=====================================================================" <<endl;
        cout << "Choose the action:"<<endl;
        cout << "1: load map from file" << endl;
        cout << "2: show all countries" << endl;
        cout << "3: show countries and its border" << endl;
        cout << "4: show all continents" << endl;
        cout << "5: validate map" << endl;
        cout << "99: exit" << endl;
        cout << "Enter your choice: ";
        cin >> input;
    }
    cout << "Cleanning memory..." <<endl;
    delete map;
    cout << "Program terminated" << endl;
    exit(1);  
}