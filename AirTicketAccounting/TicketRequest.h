/////////////////////////////////////////////
////////////      TicketRequest.h    ////////
/////////////////////////////////////////////

#pragma once
#include<list>
#include <string>

#include "FlightInfo.h"

class Board;

// ����� ������ �� �����

class TicketRequest : public FlightInfo
{
public:
	TicketRequest();
	~TicketRequest();

	// ������� ������
	void setId(int id);
	void setStatus(std::string status);
	void setPassengerName(std::string name);


	// ������� ������
	int getId() const;
	std::string getStatus()const;
	std::string getPassengerName() const;

	// ��������� ������
	void printInfo() const override; // ������ �������
	static std::list<TicketRequest> loadFromFile(const std::string& filename); // ������ ������� �� �����
	static void saveToFile(const std::list<TicketRequest>& tickets, const std::string& filename); // ���������� ������� � ����

	// ������� ������ � �������, �������� � ��������� �������
	static void workInRequest(std::list<TicketRequest>& tickets);

	// ���������� ���������� ������ �� ��������
	static void sortList(std::list<TicketRequest>& container);

	// ������� ��������� ������� ������ �� id 
	static std::list<TicketRequest>::iterator
		getTicketRequestById(std::list<TicketRequest>& tickets, int id);

	// ������� �������� ������� ������ �� �����
	static void createTicketRequest(TicketRequest* ticket, std::list<Board>& flights); // �������� ������



private:
	int id; // �������������� ����� ������
	std::string status; // ������ ������
	std::string passengerName; // ��� ���������

};

