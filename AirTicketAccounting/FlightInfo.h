/////////////////////////////////////////////
////////////      FlightInfo.h    ///////////
/////////////////////////////////////////////

#pragma once
#include <string>

// абстрактный класс с общими полями для классов Board и TicketRequest

class FlightInfo {
protected:
	std::string flightNumber; // номер рейса
	std::string departureDate; // дата вылета
	std::string destination; // пункт назначения

public:
	
	virtual void printInfo() const = 0;

	// сеттеры класса
	void setFlightNumber(const std::string value);
	void setDepartureDate(const std::string value);
	void setDestination(std::string destination);

	// геттеры класса
	std::string getFlightNumber() const;
	std::string getDepartureDate() const;
	std::string getDestination()const;
};
