#include "Package.h"

Package::Package(const std::string& name, const std::string& dropOffPoint, const std::string& dropOffDeadline)
    : name(name), dropOffPoint(dropOffPoint), dropOffDeadline(dropOffDeadline), assignedToDrone(false) {}

const std::string& Package::getName() const {
    return name;
}

const std::string& Package::getDropOffPoint() const {
    return dropOffPoint;
}

const std::string& Package::getDropOffDeadline() const {
    return dropOffDeadline;
}

bool Package::isAssignedToDrone() const {
    return assignedToDrone;
}

void Package::assignToDrone() {
    assignedToDrone = true;
}

void Package::unassignFromDrone() {
    assignedToDrone = false;
}
