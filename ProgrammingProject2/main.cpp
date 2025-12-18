#include "Vehicle.h"
#include "Car.h"
#include "Truck.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<Vehicle*> inventory;  // Inventory of vehicles (pointers to base class)
    int choice;                  // User menu choice

    do {
        // Display the main menu
        cout << "\n=== Car Dealership Inventory ===\n";
        cout << "1. Add Car\n";
        cout << "2. Add Truck\n";
        cout << "3. Print Full Inventory\n";
        cout << "4. Search Inventory\n";
        cout << "5. Print Details of a Vehicle\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(); // Clear newline character left in input buffer

        switch(choice) {
            case 1: {
                // Add a new Car to inventory
                string make, model, color;
                int mpg, msrp;
                bool spare, wiper;

                cout << "Enter make: "; getline(cin, make);
                cout << "Enter model: "; getline(cin, model);
                cout << "Enter color: "; getline(cin, color);
                cout << "Enter MPG: "; cin >> mpg;
                cout << "Enter MSRP: "; cin >> msrp;
                cout << "Spare in trunk? (0/1): "; cin >> spare;
                cout << "Rear windshield wiper? (0/1): "; cin >> wiper;
                cin.ignore();

                // Create a Car object and add it to the inventory
                inventory.push_back(new Car(make, model, color, mpg, msrp, spare, wiper));
                cout << "Car added!\n";
                break;
            }

            case 2: {
                // Add a new Truck to inventory
                string make, model, color;
                int mpg;
                double msrp;
                bool storage, tailgate;

                cout << "Enter make: "; getline(cin, make);
                cout << "Enter model: "; getline(cin, model);
                cout << "Enter color: "; getline(cin, color);
                cout << "Enter MPG: "; cin >> mpg;
                cout << "Enter MSRP: "; cin >> msrp;
                cout << "Side panel storage? (0/1): "; cin >> storage;
                cout << "Auto-release tailgate? (0/1): "; cin >> tailgate;
                cin.ignore();

                // Create a Truck object and add it to the inventory
                inventory.push_back(new Truck(make, model, color, mpg, msrp, storage, tailgate));
                cout << "Truck added!\n";
                break;
            }

            case 3: {
                // Print the full inventory of vehicles
                cout << "\n--- Full Inventory ---\n";
                for (size_t i = 0; i < inventory.size(); i++) {
                    cout << i + 1 << ".\n";
                    inventory[i]->printDetails(); // Polymorphic call
                }
                break;
            }

            case 4: {
                // Search inventory by make, model, or color
                string term;
                cout << "Enter make, model, or color to search: ";
                getline(cin, term);

                cout << "\n--- Search Results ---\n";
                for (auto v : inventory) {
                    if (v->getMake() == term || v->getModel() == term || v->getColor() == term) {
                        v->printDetails(); // Print matching vehicle
                    }
                }
                break;
            }

            case 5: {
                // Print details of a specific vehicle by index
                size_t index;
                cout << "Enter vehicle number: ";
                cin >> index;
                cin.ignore();

                if (index > 0 && index <= inventory.size()) {
                    inventory[index - 1]->printDetails(); // Polymorphic call
                } else {
                    cout << "Invalid number!\n";
                }
                break;
            }

            case 6:
                // Exit the program
                cout << "Exiting program...\n";
                break;

            default:
                // Handle invalid menu choice
                cout << "Invalid choice, try again.\n";
        }

    } while (choice != 6); // Repeat menu until user chooses to exit

    // Clean up dynamically allocated memory to prevent memory leaks
    for (auto v : inventory) {
        delete v;
    }
    inventory.clear(); // Clear the vector

    return 0;
}
