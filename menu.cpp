#include "Menu.h"
#include "filereader.h"
#include <chrono>
Menu::Menu() = default;

void Menu::start() {
    unsigned short answer;
    bool error = true;
    int dataset_number;
    std::string dataset_file;
    filereader file;
    do {
        cout <<
             "-----------------------------" << endl <<
             "|           Trips           |" << endl <<
             "|Select dataset:         1  |" << endl <<
             "|Non seperate groups:    2  |" << endl <<
             "|Seperate groups:        3  |" << endl <<
             "|Exit:                   0  |" << endl <<
             "-----------------------------" << endl;
        cin >> answer;
        if (cin.eof()) {
            exit(0);
        }
        if (!cin.good()) {
            cout << "Sadly that's not an option. Please choose another one." << std::endl;
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
            continue;
        }
        switch (answer) {
            case 1: {
                cout << "Please input the number of the dataset you wish to load: ";
                cin.clear();
                cin >> dataset_number;
                if(dataset_number < 10)
                    dataset_file = "../Tests/in0" + std::to_string(dataset_number) +".txt";
                else
                    dataset_file = "../Tests/in" + std::to_string(dataset_number) +".txt";
                file.load_database(dataset_file);
                std::cout << "Dataset loaded successfully!\n";
                break;
            }
            case 2: {

                break;
            }

            case 3: {

                break;
            }

            case 0:
                exit(0);
            default:
                cout << "Sadly that's not an option. Please choose another one." << endl;
        }
    } while (error);
}