#include "menu.h"
#include "filereader.h"
#include <chrono>
#include "graph2.h"

Menu::Menu() = default;

void Menu::start() {

    Graph2 g(0, true);
    unsigned short answer;
    bool error = true;
    int dataset_number;
    std::string dataset_file;
    filereader file;
    do {
        cout <<
             "-----------------------------" << endl <<
             "|           Trips           |" << endl <<
             "|1.1:                    1  |" << endl <<
             "|1.2:                    2  |" << endl <<
             "|Separate groups:        3  |" << endl <<
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
                g = file.load_database(dataset_file);
                std::cout << "Dataset loaded successfully!\n";

                pair <int, int> p1 = file.chooseNodes(g, 1);

                g.maxFlow(p1.first, p1.second);
                error = false;
                break;
            }
            case 2: {
                cout << "Please input the number of the dataset you wish to load: ";
                cin.clear();
                cin >> dataset_number;

                if(dataset_number < 10)
                    dataset_file = "../Tests/in0" + std::to_string(dataset_number) +".txt";
                else
                    dataset_file = "../Tests/in" + std::to_string(dataset_number) +".txt";
                g = file.load_database(dataset_file);
                std::cout << "Dataset loaded successfully!\n";

                pair <int, int> p1 = file.chooseNodes(g, 1);

                g.scenario2(p1.first, p1.second);
                error = false;
                break;
            }
            case 3: {
                cout << "Please input the number of the dataset you wish to load: ";
                cin.clear();
                cin >> dataset_number;
                if(dataset_number < 10)
                    dataset_file = "../Tests/in0" + std::to_string(dataset_number) +".txt";
                else
                    dataset_file = "../Tests/in" + std::to_string(dataset_number) +".txt";
                g = file.load_database(dataset_file);
                std::cout << "Dataset loaded successfully!\n";
                error = false;
                break;
            }

            case 0:
                exit(0);
            default:
                cout << "Sadly that's not an option. Please choose another one." << endl;
        }
    } while (error);
}