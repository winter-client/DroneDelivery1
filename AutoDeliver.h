#ifndef AUTODELIVER_H
#define AUTODELIVER_H

#include <vector>
#include <string>

#include "Drone.h"
#include "Package.h"

class AutoDeliver
{	// attribute declaration
	// vector usage for dynamic size array. We can't determine how many instances of objects are being created
	std::vector <Drone> drones;
	std::vector <Package> packages;

public:
	// method declaration
	// add/remove/edit methods that can be inherited for both drone and package
	void addObject();
	void removeObject();
	void editObject();

	void matchingPlan();
	void saveMatchingPlan();
	void displayMatchingPlan();
	void displayUnassignedDrone();
	void displayUnassignedPackage();

	// This is for the location destination and time for drone to charge. Is this supposed to be here? Or in individual? But if same location can -
	// - just inherit right?
	void timeDue(int);
	void locationDue(std::string);









};

#endif