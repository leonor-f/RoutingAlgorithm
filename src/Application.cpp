//
// Created by leono on 01/05/2024.
//

#include "Application.h"

#include "FileReader.h"
#include <iostream>

using namespace std;

Application::Application() {
    menu();
}

void Application::menu() {
    int choice;

    do {
        cout << endl << "+-----------------------------------------------------------------------------+" << endl;
        cout << "|  Welcome to the Routing Algorithm for Ocean Shipping and Urban Deliveries!  |" << endl;
        cout << "|                             We hope to be useful!                           |" << endl;
        cout << "+-----------------------------------------------------------------------------+" << endl << endl;
        cout << "1. Load and parse data" << endl;
        cout << "2. Backtracking Algorithm" << endl;
        cout << "3. Triangular Approximation Heuristic" << endl;
        cout << "4. Other Heuristics" << endl;
        cout << "5. TSP in the Real World" << endl << endl;

        cout << "0. Exit" << endl << endl;
        cout << "Enter your choice and press ENTER: ";
        cin >> choice;

        string sel;
        switch (choice) {
            case 1:
                loadData();
                break;
            case 2:
                backtracking();
                break;
            case 3:
                triangular();
                break;
            case 4:
                other();
                break;
            case 5:
                cout << "Enter the **origin** of the Travelling Salesperson Problem: ";
                cin >> sel;
                realWorld(sel);
                break;
            case 0:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void Application::loadData() {
    int choice;

    do {
        cout << endl;
        cout << "1. Toy Graph" << endl;
        cout << "2. Extra Medium-Size Graphs" << endl;
        cout << "3. Real-world Graphs" << endl << endl;

        cout << "0. Go back" << endl << endl;
        cout << "Enter your choice and press ENTER: ";
        cin >> choice;

        string sel;
        switch (choice) {
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 0:
                menu();
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void Application::backtracking() {

    goBack();
}

void Application::triangular() {

    goBack();
}

void Application::other() {

    goBack();
}

void Application::realWorld(string c) {
    // cout << "Path does not exist! << endl;
    goBack();
}

void Application::goBack() {
    cout << endl << "---------------------------" << endl << "Press ENTER to go back." << endl
         << "---------------------------" << endl;
    menu();
}
