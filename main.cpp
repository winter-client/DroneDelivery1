#include <iostream>
#include <string>
#include "Drone.h"
#include "Package.h"
#include "AutoDeliver.h"

using namespace std;

int main() {
    AutoDeliver autoDeliver;
    string droneDataFilePath, packageDataFilePath;

    // Input the file paths for drone and package data
    cout << "Enter the drone data file path: ";
    cin >> droneDataFilePath;
    cout << "Enter the package data file path: ";
    cin >> packageDataFilePath;

    // Load drone and package data
    autoDeliver.loadDroneData(droneDataFilePath);
    autoDeliver.loadPackageData(packageDataFilePath);

    // Generate matching plan
    autoDeliver.generateMatchingPlan();

    // Display matching plan
    autoDeliver.displayMatchingPlan();

    // Save matching plan to a file
    string matchingPlanFilePath;
    cout << "Enter the file path to save the matching plan: ";
    cin >> matchingPlanFilePath;
    autoDeliver.saveMatchingPlanToFile(matchingPlanFilePath);

    // User interface for add/edit/delete
    int choice;
    string name, destination, rechargeDeadline, dropOffPoint, dropOffDeadline;
    while (true) {
        cout << "==================================" << endl;
        cout << "1. Add Drone" << endl;
        cout << "2. Add Package" << endl;
        cout << "3. Edit Drone" << endl;
        cout << "4. Edit Package" << endl;
        cout << "5. Delete Drone" << endl;
        cout << "6. Delete Package" << endl;
        //cout << "7. Save Matching Plan" << endl;
        //cout << "8. Display Matching Plan" << endl;
        cout << "0. Exit" << endl;
        cout << "==================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter drone name: ";
            cin >> name;

            // Check if the drone already exists in the matching plan
            if (autoDeliver.droneExists(name)) {
                cout << "Drone with the same name already exists in the matching plan." << endl;
            }
            else {
                cout << "Enter destination: ";
                cin >> destination;
                cout << "Enter recharge deadline: ";
                cin >> rechargeDeadline;
                autoDeliver.addDrone(droneDataFilePath, name, destination, rechargeDeadline);
            }
            break;
        case 2:
            cout << "Enter package name: ";
            cin >> name;

            // Check if the package already exists in the matching plan
            if (autoDeliver.packageExists(name)) {
                cout << "Package with the same name already exists in the matching plan." << endl;
            }
            else {
                cout << "Enter drop-off point: ";
                cin >> dropOffPoint;
                cout << "Enter drop-off deadline: ";
                cin >> dropOffDeadline;
                autoDeliver.addPackage(packageDataFilePath, name, dropOffPoint, dropOffDeadline);
            }
            break;
        case 3:
            cout << "Enter drone name to edit: ";
            cin >> name;

            // Check if the drone exists in the matching plan
            if (!autoDeliver.droneExists(name)) {
                cout << "Drone with the specified name does not exist in the matching plan." << endl;
            }
            else {
                cout << "Enter new destination: ";
                cin >> destination;
                cout << "Enter new recharge deadline: ";
                cin >> rechargeDeadline;
                autoDeliver.editDrone(droneDataFilePath,name, destination, rechargeDeadline);
            }
            break;
        case 4:
            cout << "Enter package name to edit: ";
            cin >> name;

            // Check if the package exists in the matching plan
            if (!autoDeliver.packageExists(name)) {
                cout << "Package with the specified name does not exist in the matching plan." << endl;
            }
            else {
                cout << "Enter new drop-off point: ";
                cin >> dropOffPoint;
                cout << "Enter new drop-off deadline: ";
                cin >> dropOffDeadline;
                autoDeliver.editPackage(packageDataFilePath,name, dropOffPoint, dropOffDeadline);
            }
            break;
        case 5:
            cout << "Enter drone name to delete: ";
            cin >> name;

            // Check if the drone exists in the matching plan
            if (!autoDeliver.droneExists(name)) {
                cout << "Drone with the specified name does not exist in the matching plan." << endl;
            }
            else {
                autoDeliver.deleteDrone(droneDataFilePath, name);
            }
            break;
        case 6:
            cout << "Enter package name to delete: ";
            cin >> name;

            // Check if the package exists in the matching plan
            if (!autoDeliver.packageExists(name)) {
                cout << "Package with the specified name does not exist in the matching plan." << endl;
            }
            else {
                autoDeliver.deletePackage(packageDataFilePath, name);
            }
            break;
        case 0:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cerr << "Invalid choice. Please try again." << endl;
        }

        // Regenerate and display the updated matching plan
        autoDeliver.generateMatchingPlan();
        autoDeliver.displayMatchingPlan();
    }

    return 0;
}
