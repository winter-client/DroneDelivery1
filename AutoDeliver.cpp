#include "AutoDeliver.h"
#include "Package.h"
#include "Drone.h"

void AutoDeliver::loadDroneData(const std::string& droneDataFilePath) {
    std::ifstream file(droneDataFilePath);
    if (file.is_open()) {
        std::string line;
        // Check if the file is empty
        if (file.peek() != std::ifstream::traits_type::eof()) {
            // Skip the header line
            getline(file, line);
        }
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string name, destination, rechargeDeadline;
            getline(ss, name, ',');
            getline(ss, destination, ',');
            getline(ss, rechargeDeadline, ',');
            drones.push_back(Drone(name, destination, rechargeDeadline));
        }
        file.close();
    }
    else {
        std::cerr << "Error opening drone data file." << std::endl;
    }
}

void AutoDeliver::loadPackageData(const std::string& packageDataFilePath) {
    std::ifstream file(packageDataFilePath);
    if (file.is_open()) {
        std::string line;
        // Check if the file is empty
        if (file.peek() != std::ifstream::traits_type::eof()) {
            // Skip the header line
            getline(file, line);
        }
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string name, dropOffPoint, dropOffDeadline;
            getline(ss, name, ',');
            getline(ss, dropOffPoint, ',');
            getline(ss, dropOffDeadline, ',');
            packages.push_back(Package(name, dropOffPoint, dropOffDeadline));
        }
        file.close();
    }
    else {
        std::cerr << "Error opening package data file." << std::endl;
    }
}


void AutoDeliver::generateMatchingPlan() {
    // Sort drones and packages based on drop-off points
    std::sort(drones.begin(), drones.end(), [](const Drone& a, const Drone& b) {
        return a.getDestination() < b.getDestination();
        });
    std::sort(packages.begin(), packages.end(), [](const Package& a, const Package& b) {
        return a.getDropOffPoint() < b.getDropOffPoint();
        });

    // Reset package assignments for drones
    for (auto& drone : drones) {
        drone.unassignPackage();
    }

    // Assign packages to drones with the same drop-off points and within the recharge deadline
    for (auto& drone : drones) {
        if (!drone.hasPackageAssigned()) {
            for (auto& package : packages) {
                if (!package.isAssignedToDrone() && drone.getDestination() == package.getDropOffPoint() &&
                    drone.getRechargeDeadline() >= package.getDropOffDeadline()) {
                    drone.assignPackage();
                    package.assignToDrone();
                    break;
                }
            }
        }
    }
}

void AutoDeliver::displayMatchingPlan() const {
    std::cout << "Matching Plan:" << std::endl;
    bool hasMatchingPlan = false;

    for (const Drone& drone : drones) {
        bool hasPackageAssigned = false;
        std::cout << "Drone " << drone.getName() << " (Destination: " << drone.getDestination() << ", Recharge Deadline: " << drone.getRechargeDeadline() << ") -> Packages: ";

        for (const Package& package : packages) {
            if (package.isAssignedToDrone() && package.getDropOffPoint() == drone.getDestination()) {
                if (!hasPackageAssigned) {
                    hasPackageAssigned = true;
                    hasMatchingPlan = true;
                }
                std::cout << package.getName() << " (Drop-off Point: " << package.getDropOffPoint() << ", Drop-off Deadline: " << package.getDropOffDeadline() << ") ";
            }
        }

        if (!hasPackageAssigned) {
            std::cout << "No package assigned.";
        }

        std::cout << std::endl;
    }

    if (!hasMatchingPlan) {
        std::cout << "No matching plan found." << std::endl;
    }

    // Display unassigned packages
    bool hasUnassignedPackages = false;

    for (const Package& package : packages) {
        if (!package.isAssignedToDrone()) {
            if (!hasUnassignedPackages) {
                hasUnassignedPackages = true;
                std::cout << "Unassigned Packages:" << std::endl;
            }

            std::cout << "Package " << package.getName() << " (Drop-off Point: " << package.getDropOffPoint() << ", Drop-off Deadline: " << package.getDropOffDeadline() << ")" << std::endl;
        }
    }

    if (!hasMatchingPlan && !hasUnassignedPackages) {
        std::cout << "No matching plan found. No unassigned packages." << std::endl;
    }
}


void AutoDeliver::saveMatchingPlanToFile(const std::string& filePath) const {
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << "Matching Plan:" << std::endl;
        bool hasMatchingPlan = false;

        for (const Drone& drone : drones) {
            if (drone.hasPackageAssigned()) {
                file << drone.getName() << "," << drone.getDestination() << "," << drone.getRechargeDeadline() << ",";
                bool hasPackageAssigned = false;
                for (const Package& package : packages) {
                    if (package.isAssignedToDrone() && package.getDropOffPoint() == drone.getDestination()) {
                        if (!hasPackageAssigned) {
                            file << package.getName();
                            hasPackageAssigned = true;
                        }
                        else {
                            file << ";" << package.getName();
                        }
                    }
                }
                file << std::endl;
                hasMatchingPlan = true;
            }
        }

        if (!hasMatchingPlan) {
            file << "No matching plan found." << std::endl;
        }

        // Display unassigned packages
        bool hasUnassignedPackages = false;

        for (const Package& package : packages) {
            if (!package.isAssignedToDrone()) {
                if (!hasUnassignedPackages) {
                    hasUnassignedPackages = true;
                    file << "Unassigned Packages:" << std::endl;
                }

                file << package.getName() << "," << package.getDropOffPoint() << "," << package.getDropOffDeadline() << std::endl;
            }
        }

        if (!hasMatchingPlan && !hasUnassignedPackages) {
            file << "No matching plan found. No unassigned packages." << std::endl;
        }

        file.close();
        std::cout << "Matching plan saved successfully." << std::endl;
    }
    else {
        std::cerr << "Error opening the matching plan file." << std::endl;
    }
}

void AutoDeliver::addDrone(const std::string& filePath, const std::string& name, const std::string& destination, const std::string& rechargeDeadline) {
    drones.push_back(Drone(name, destination, rechargeDeadline));

    std::ofstream file(filePath, std::ios::app); // Open file in append mode
    if (file.is_open()) {
        // Check if the file is empty
        std::ifstream checkFile(filePath);
        bool isEmpty = checkFile.peek() == std::ifstream::traits_type::eof();
        checkFile.close();

        if (isEmpty) {
            file << "Name,Destination,Recharge Deadline" << std::endl; // Write the header line
        }

        file << name << "," << destination << "," << rechargeDeadline << std::endl;
        file.close();

        if (isEmpty) {
            std::cout << "Drone added successfully." << std::endl;
        }
        else {
            std::cout << "Drone data appended successfully." << std::endl;
        }

        generateMatchingPlan();
    }
    else {
        std::cerr << "Error opening the file." << std::endl;
    }
}

void AutoDeliver::addPackage(const std::string& filePath, const std::string& name, const std::string& dropOffPoint, const std::string& dropOffDeadline) {
    packages.push_back(Package(name, dropOffPoint, dropOffDeadline));

    std::ofstream file(filePath, std::ios::app); // Open file in append mode
    if (file.is_open()) {
        // Check if the file is empty
        std::ifstream checkFile(filePath);
        bool isEmpty = checkFile.peek() == std::ifstream::traits_type::eof();
        checkFile.close();

        if (isEmpty) {
            file << "Name,Drop-off Point,Drop-off Deadline" << std::endl; // Write the header line
        }

        file << name << "," << dropOffPoint << "," << dropOffDeadline << std::endl;
        file.close();

        if (isEmpty) {
            std::cout << "Package added successfully." << std::endl;
        }
        else {
            std::cout << "Package data appended successfully." << std::endl;
        }

        generateMatchingPlan();
    }
    else {
        std::cerr << "Error opening the file." << std::endl;
    }
}





void AutoDeliver::editDrone(const std::string& name, const std::string& destination, const std::string& rechargeDeadline) {
    for (auto& drone : drones) {
        if (drone.getName() == name) {
            drone = Drone(name, destination, rechargeDeadline);
            break;
        }
    }
}

void AutoDeliver::editPackage(const std::string& name, const std::string& dropOffPoint, const std::string& dropOffDeadline) {
    for (auto& package : packages) {
        if (package.getName() == name) {
            package = Package(name, dropOffPoint, dropOffDeadline);
            break;
        }
    }
}

void AutoDeliver::deleteDrone(const std::string& filePath, const std::string& name) {
    drones.erase(std::remove_if(drones.begin(), drones.end(), [name](const Drone& drone) {
        return drone.getName() == name;
        }), drones.end());

    // Update the file contents
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << "Name,Destination,Recharge Deadline" << std::endl; // Write the header line
        for (const Drone& drone : drones) {
            file << drone.getName() << "," << drone.getDestination() << "," << drone.getRechargeDeadline() << std::endl;
        }
        file.close();
        std::cout << "Drone deleted successfully." << std::endl;
        generateMatchingPlan();
    }
    else {
        std::cerr << "Error opening the file." << std::endl;
    }
}

void AutoDeliver::deletePackage(const std::string& filePath, const std::string& name) {
    packages.erase(std::remove_if(packages.begin(), packages.end(), [name](const Package& package) {
        return package.getName() == name;
        }), packages.end());

    // Update the file contents
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << "Name,Drop-off Point,Drop-off Deadline" << std::endl; // Write the header line
        for (const Package& package : packages) {
            file << package.getName() << "," << package.getDropOffPoint() << "," << package.getDropOffDeadline() << std::endl;
        }
        file.close();
        std::cout << "Package deleted successfully." << std::endl;
        generateMatchingPlan();
    }
    else {
        std::cerr << "Error opening the file." << std::endl;
    }
}

