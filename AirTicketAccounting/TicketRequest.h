#pragma once
#include <string>

class TicketRequest
{
public:
	TicketRequest();
	~TicketRequest();

	// ������� ������
	void setId(int id);
	void setFlightNumber(std::string fl_num);
	void setPassengerName(std::string name);
	void setDepartureDate(std::string name);
	void setDestination(std::string destination);
	void setStatus(std::string status);

	// ������� ������
	int getId() const;
	std::string getPassengerName() const;
	std::string getFlightNumber()const;
	std::string getDepartureDate()const;
	std::string getDestination()const;
	std::string getStatus()const;

	// ��������� ������
	void printTicket() const; // ������ �������
	static void saveToFile(const std::list<TicketRequest>& tickets, const std::string& filename); // ���������� ������� � ����
	static std::list<TicketRequest> loadFromFile(const std::string& filename); // ������ ������� �� �����

private:
	int id;
	std::string passengerName;
	std::string flightNumber;
	std::string departurDate;
	std::string destination;
	std::string status;
};

