#include "AutoDeliver.h"
#include "Package.h"
#include "Drone.h"

void AutoDeliver::loadDroneData(const std::string& droneDataFilePath) {
    std::ifstream file(droneDataFilePath);
    if (file.is_open()) {
        std::string line;
        // Skip the header line
        getline(file, line);
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
        std::cout << "Error opening drone data file." << std::endl;
    }
}

void AutoDeliver::loadPackageData(const std::string& packageDataFilePath) {
    std::ifstream file(packageDataFilePath);
    if (file.is_open()) {
        std::string line;
        // Skip the header line
        getline(file, line);
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
        std::cout << "Error opening package data file." << std::endl;
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

    // Assign packages to drones with the same drop-off points
    for (auto& drone : drones) {
        if (!drone.hasPackageAssigned()) {
            for (auto& package : packages) {
                if (!package.isAssignedToDrone() && drone.getDestination() == package.getDropOffPoint()) {
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
    bool hasUnassignedPackages = true;
    for (const Package& package : packages) {
        if (!package.isAssignedToDrone()) {
            std::cout << "Package " << package.getName() << " (Drop-off Point: " << package.getDropOffPoint() << ", Drop-off Deadline: " << package.getDropOffDeadline() << ") is not assigned to any drone." << std::endl;
            hasUnassignedPackages = false;
        }
    }

    if (!hasMatchingPlan && !hasUnassignedPackages) {
        std::cout << "No matching plan found. No unassigned packages." << std::endl;
    }
}

void AutoDeliver::saveMatchingPlanToFile(const std::string& filePath) const {
    std::ofstream file(filePath);
    if (file.is_open()) {
        for (const Drone& drone : drones) {
            if (drone.hasPackageAssigned()) {
                file << "Drone " << drone.getName() << " (Destination: " << drone.getDestination() << ", Recharge Deadline: " << drone.getRechargeDeadline() << ") -> Package ";
                for (const Package& package : packages) {
                    if (package.isAssignedToDrone() && package.getDropOffPoint() == drone.getDestination()) {
                        file << package.getName();
                        break;
                    }
                }
                file << std::endl;
            }
        }
        file.close();
    }
    else {
        std::cout << "Error opening the matching plan file." << std::endl;
    }
}

void AutoDeliver::addDrone(const std::string& name, const std::string& destination, const std::string& rechargeDeadline) {
    drones.push_back(Drone(name, destination, rechargeDeadline));
}

void AutoDeliver::addPackage(const std::string& name, const std::string& dropOffPoint, const std::string& dropOffDeadline) {
    packages.push_back(Package(name, dropOffPoint, dropOffDeadline));
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

void AutoDeliver::deleteDrone(const std::string& name) {
    drones.erase(std::remove_if(drones.begin(), drones.end(), [name](const Drone& drone) {
        return drone.getName() == name;
        }), drones.end());
}

void AutoDeliver::deletePackage(const std::string& name) {
    packages.erase(std::remove_if(packages.begin(), packages.end(), [name](const Package& package) {
        return package.getName() == name;
        }), packages.end());
}
