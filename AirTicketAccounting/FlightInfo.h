/////////////////////////////////////////////
////////////      FlightInfo.h    ///////////
/////////////////////////////////////////////

#pragma once
#include <string>

// ����������� ����� � ������ ������ ��� ������� Board � TicketRequest

class FlightInfo {
protected:
	std::string flightNumber; // ����� �����
	std::string departureDate; // ���� ������
	std::string destination; // ����� ����������

public:
	
	virtual void printInfo() const = 0;

	// ������� ������
	void setFlightNumber(const std::string value);
	void setDepartureDate(const std::string value);
	void setDestination(std::string destination);

	// ������� ������
	std::string getFlightNumber() const;
	std::string getDepartureDate() const;
	std::string getDestination()const;
};
