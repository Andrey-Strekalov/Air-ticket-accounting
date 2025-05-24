/////////////////////////////////////////////
/////////      FlightInfo.cpp     ///////////
/////////////////////////////////////////////



#include <iostream>
#include "FlightInfo.h"


void FlightInfo::setFlightNumber(const std::string value) { flightNumber = value; }
void FlightInfo::setDepartureDate(const std::string value) { departureDate = value; }
void FlightInfo::setDestination(std::string value) { destination = value; }


std::string FlightInfo::getFlightNumber() const { return flightNumber; }
std::string FlightInfo::getDepartureDate() const { return departureDate; }
std::string FlightInfo::getDestination()const { return  destination; }
