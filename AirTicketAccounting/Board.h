/////////////////////////////////////////////
////////////      Board.h    ////////////////
/////////////////////////////////////////////

#pragma once

#include <list>
#include <string>
#include "FlightInfo.h"

class TicketRequest;

// ����� ���������� �����

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
	void printInfo() const override; // ����� ���������� � �����
	void printPassengersList() const; // ����� ������ ����������
	void calculateAvailableSeats(); // ���������� ���������� ��������� ����
	void addPassenger(const TicketRequest& ticket); // ���������� ��������� � ������

	static std::list<Board> loadFromFile(const std::string& filename); // ������ ������� �� �����
	static void saveToFile(const std::list<Board>& flights, const std::string& filename); // ���������� ������� � ����
	// ����������� ������ ���������� (�������� � ���� � ������� addPassenger())
	static void assignPassengers(std::list<Board>& flights, std::list<TicketRequest>& tickets); 
	static void flightChekIn(Board* flights); // ����������� ��������� �� ����

private:
	int capacity = 0; // �����������
	int availableSeats = 0; // ��������� �����
	std::string aircraftNumber; // ��������������� ����� ���������� �����
	std::list<TicketRequest> passengers; // ������ ����������
};