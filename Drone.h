#ifndef DRONE_H
#define DRONE_H

#include <iostream>
#include <string>

#include "Package.h"
#include "AutoDeliver.h"

class Drone {
private:
    std::string name;
    std::string destination;
    std::string rechargeDeadline;
    bool hasPackage;

public:
    Drone(const std::string& name, const std::string& destination, const std::string& rechargeDeadline);
    const std::string& getName() const;
    const std::string& getDestination() const;
    const std::string& getRechargeDeadline() const;
    bool hasPackageAssigned() const;
    void assignPackage();
    void unassignPackage();
};

#endif