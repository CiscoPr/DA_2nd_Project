#include "Menu.h"
#include <chrono>
Menu::Menu() = default;

void Menu::start() {
    unsigned short answer;
    bool error = true;

    do {
        cout <<
             "-----------------------------" << endl <<
             "|        Deliveries         |" << endl <<
             "|Non seperate groups     1  |" << endl <<
             "|Seperate groups :       2  |" << endl <<
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

                break;
            }
            case 2: {

                break;
            }

            case 0:
                exit(0);
            default:
                cout << "Sadly that's not an option. Please choose another one." << endl;
        }
    } while (error);
}