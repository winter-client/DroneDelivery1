#include "Drone.h"

Drone::Drone(const std::string& name, const std::string& destination, const std::string& rechargeDeadline)
    : name(name), destination(destination), rechargeDeadline(rechargeDeadline), hasPackage(false) {}

const std::string& Drone::getName() const {
    return name;
}

const std::string& Drone::getDestination() const {
    return destination;
}

const std::string& Drone::getRechargeDeadline() const {
    return rechargeDeadline;
}

bool Drone::hasPackageAssigned() const {
    return hasPackage;
}

void Drone::assignPackage() {
    hasPackage = true;
}

void Drone::unassignPackage() {
    hasPackage = false;
}
