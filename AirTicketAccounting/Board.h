/////////////////////////////////////////////
////////////      Board.h    ////////////////
/////////////////////////////////////////////

#pragma once

#include <list>
#include <string>
#include "FlightInfo.h"

class TicketRequest;



class Board : public FlightInfo {
public:
	Board();
	~Board();

	// �������
	
	void setCapacity(int value);
	void setAvailableSeats(int value);
	void setAircraftNumber(const std::string& value);

	// �������
	int getCapacity() const;
	int getAvailableSeats() const;
	std::string getAircraftNumber() const;
	const std::list<TicketRequest>& getPassengers() const;

	// ������
	void printInfo() const;
	void calculateAvailableSeats();
	void printPassengersList() const;
	void addPassenger(const TicketRequest& ticket);

	static std::list<Board> loadFromFile(const std::string& filename); // ������ ������� �� �����
	static void saveToFile(const std::list<Board>& flights, const std::string& filename); // ���������� ������� � ����
	static void assignPassengers(std::list<Board>& flights, std::list<TicketRequest>& tickets);
	//static void changeFlightDate(std::list<Board>& flights);


	// ����������� ��������� �� ����
	static void flightChekIn(Board* flights);

private:
	int capacity;
	int availableSeats;
	std::string aircraftNumber;
	std::list<TicketRequest> passengers;
};