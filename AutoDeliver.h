#ifndef AUTODELIVER_H
#define AUTODELIVER_H

#include "Drone.h"
#include "Package.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

class Drone;
class Package;

class AutoDeliver {
private:
    std::vector<Drone> drones;
    std::vector<Package> packages;

public:
    void loadDroneData(const std::string& droneDataFilePath);
    void loadPackageData(const std::string& packageDataFilePath);
    void generateMatchingPlan();
    void displayMatchingPlan() const;
    void saveMatchingPlanToFile(const std::string& filePath) const;
    void addDrone(const std::string& filePath, const std::string& name, const std::string& destination, const std::string& rechargeDeadline);
    void addPackage(const std::string& filePath, const std::string& name, const std::string& dropOffPoint, const std::string& dropOffDeadline);
    void editDrone(const std::string& filePath, const std::string& name, const std::string& destination, const std::string& rechargeDeadline);
    void editPackage(const std::string& filePath, const std::string& name, const std::string& dropOffPoint, const std::string& dropOffDeadline);
    void deleteDrone(const std::string& filePath, const std::string& name);
    void deletePackage(const std::string& filePath, const std::string& name);
    bool droneExists(const std::string& name) const;
    bool packageExists(const std::string& name) const;
};

#endif