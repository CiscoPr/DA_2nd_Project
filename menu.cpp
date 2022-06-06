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
             "|2.1                     3  |" << endl <<
             "|2.2                     4  |" << endl <<
             "|2.3                     5  |" << endl <<
             "|2.4                     6  |" << endl <<
             "|2.5                     7  |" << endl <<
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
                interfaceNodes(g, file, dataset_number, dataset_file);

                pair <int, int> p1 = file.chooseNodes(g, 1);
                g.maxFlow(p1.first, p1.second);

                error = false;
                break;
            }
            case 2: {
                interfaceNodes(g, file, dataset_number, dataset_file);

                pair <int, int> p1 = file.chooseNodes(g, 1);
                g.scenario2(p1.first, p1.second);

                error = false;
                break;
            }
            case 3: {
                int dim;
                interfaceNodes(g, file, dataset_number, dataset_file);

                pair <int, int> p1 = file.chooseNodes(g, 1);
                cout << "Please input a dimension for a group: ";
                cin >> dim;
                g.random_dimension_divided_groups(g, p1.first, p1.second, dim);
                error = false;
                break;
            }
            case 4: {
                int dim, incr;
                interfaceNodes(g, file, dataset_number, dataset_file);

                pair <int, int> p1 = file.chooseNodes(g, 1);
                cout << "Please input a dimension for a group: ";
                cin >> dim;
                cout << "Now, please input the number you want to be added to that dimension: ";
                cin >> incr;
                g.random_dimension_divided_groups(g, p1.first, p1.second, (dim+incr));
                //g.edmondskarp(g, p1.first, p1.second);
                error = false;
                break;
            }
            case 5: {
                interfaceNodes(g, file, dataset_number, dataset_file);

                pair <int, int> p1 = file.chooseNodes(g, 1);

                g.edmondskarp(g, p1.first, p1.second);
                error = false;
                break;
            }
            case 6: {
                interfaceNodes(g, file, dataset_number, dataset_file);

                pair <int, int> p1 = file.chooseNodes(g, 1);

                g.minimum_time(g, p1.first, p1.second);
                error = false;
                break;
            }
            case 7: {
                interfaceNodes(g, file, dataset_number, dataset_file);

                pair <int, int> p1 = file.chooseNodes(g, 1);

                //g.edmondskarp(g, p1.first, p1.second);
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

void Menu::interfaceNodes(Graph2 &g, filereader &file, int &dataset_number, string &dataset_file) {
    cout << "Please input the number of the dataset you wish to load: ";
    cin.clear();
    cin >> dataset_number;

    if(dataset_number < 10)
        dataset_file = "../Tests/in0" + to_string(dataset_number) +".txt";
    else
        dataset_file = "../Tests/in" + to_string(dataset_number) +".txt";
    g = file.load_database(dataset_file);
    cout << "Dataset loaded successfully!\n" << endl;
}



