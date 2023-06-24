#ifndef Package_H
#define Package_H

#include <iostream>
#include <string>
#include "Drone.h"
#include "AutoDeliver.h"

class Package {
private:
    std::string name;
    std::string dropOffPoint;
    std::string dropOffDeadline;
    bool assignedToDrone;

public:
    Package(const std::string& name, const std::string& dropOffPoint, const std::string& dropOffDeadline);
    const std::string& getName() const;
    const std::string& getDropOffPoint() const;
    const std::string& getDropOffDeadline() const;
    bool isAssignedToDrone() const;
    void assignToDrone();
    void unassignFromDrone();
};

#endif
