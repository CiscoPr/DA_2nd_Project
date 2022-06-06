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
                chrono::high_resolution_clock::time_point start1, end1;
                start1 = chrono::high_resolution_clock::now();
                g.maxFlow(p1.first, p1.second);
                end1 = chrono::high_resolution_clock::now();
                cout << '\n' << "total of " << chrono::duration_cast<chrono::microseconds>(end1-start1).count() << " elapsed microseconds";

                error = false;
                break;
            }
            case 2: {
                interfaceNodes(g, file, dataset_number, dataset_file);

                pair <int, int> p1 = file.chooseNodes(g, 1);
                chrono::high_resolution_clock::time_point start2, end2;
                start2 = chrono::high_resolution_clock::now();
                g.scenario2(p1.first, p1.second);
                end2 = chrono::high_resolution_clock::now();
                cout << '\n' << "total of " << chrono::duration_cast<chrono::microseconds>(end2-start2).count() << " elapsed microseconds";

                error = false;
                break;
            }
            case 3: {
                int dim;
                interfaceNodes(g, file, dataset_number, dataset_file);

                pair <int, int> p1 = file.chooseNodes(g, 1);
                cout << "Please input a dimension for a group: ";
                cin >> dim;
                chrono::high_resolution_clock::time_point start3, end3;
                start3 = chrono::high_resolution_clock::now();
                g.random_dimension_divided_groups(g, p1.first, p1.second, dim);
                end3 = chrono::high_resolution_clock::now();
                cout << '\n' << "total of " << chrono::duration_cast<chrono::microseconds>(end3-start3).count() << " elapsed microseconds";
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
                chrono::high_resolution_clock::time_point start4, end4;
                start4 = chrono::high_resolution_clock::now();
                g.random_dimension_divided_groups(g, p1.first, p1.second, (dim+incr));
                //g.edmondskarp(g, p1.first, p1.second);
                end4 = chrono::high_resolution_clock::now();
                cout << '\n' << "total of " << chrono::duration_cast<chrono::microseconds>(end4-start4).count() << " elapsed microseconds";
                error = false;
                break;
            }
            case 5: {
                interfaceNodes(g, file, dataset_number, dataset_file);

                pair <int, int> p1 = file.chooseNodes(g, 1);

                chrono::high_resolution_clock::time_point start5, end5;
                start5 = chrono::high_resolution_clock::now();
                g.edmondskarp(g, p1.first, p1.second);
                end5 = chrono::high_resolution_clock::now();
                cout << '\n' << "total of " << chrono::duration_cast<chrono::microseconds>(end5-start5).count() << " elapsed microseconds";
                error = false;
                break;
            }
            case 6: {
                interfaceNodes(g, file, dataset_number, dataset_file);

                pair <int, int> p1 = file.chooseNodes(g, 1);

                chrono::high_resolution_clock::time_point start6, end6;
                start6 = chrono::high_resolution_clock::now();
                g.minimum_time(g, p1.first, p1.second);
                end6 = chrono::high_resolution_clock::now();
                cout << '\n' << "total of " << chrono::duration_cast<chrono::microseconds>(end6-start6).count() << " elapsed microseconds";
                error = false;
                break;
            }
            case 7: {
                int dim;
                interfaceNodes(g, file, dataset_number, dataset_file);

                pair <int, int> p1 = file.chooseNodes(g, 1);

                cout << "Please input a dimension for a group: ";
                cin >> dim;
                vector<vector<int>> path;
                chrono::high_resolution_clock::time_point start7, end7;
                start7 = chrono::high_resolution_clock::now();
                path = g.random_dimension_divided_groups(g, p1.first, p1.second, dim);
                g.maximum_wait_time(g, path);
                end7 = chrono::high_resolution_clock::now();
                cout << '\n' << "total of " << chrono::duration_cast<chrono::microseconds>(end7-start7).count() << " elapsed microseconds";
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



