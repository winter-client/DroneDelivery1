#ifndef DRONE_H
#define DRONE_H

#include <string>


class Drone
{
	std::string droneName;
	int batteryLevel, batteryCharge;

public:
	void setName(std::string);
	void getName(std::string);
	void setBattery(int);
	void getBattery(int);






};

#endif