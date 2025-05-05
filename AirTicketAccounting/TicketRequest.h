#pragma once
#include <string>

class TicketRequest
{
public:
	TicketRequest();
	~TicketRequest();

	void setId(int id);
	void setFlightNumber(std::string fl_num);
	void setPassengerName(std::string name);
	void setDepartureDate(std::string name);
	void setDestination(std::string destination);
	void setStatus(std::string status);

	int getId();
	std::string getPassengerName();
	std::string getFlightNumber();
	std::string getDepartureDate();
	std::string getDestination();
	std::string getStatus();


private:
	int id;
	std::string passengerName;
	std::string flightNumber;
	std::string departurDate;
	std::string destination;
	std::string status;
};

