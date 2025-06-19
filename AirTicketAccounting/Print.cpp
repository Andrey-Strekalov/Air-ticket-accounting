/////////////////////////////////////////////
////////////      Print.cpp     /////////////
/////////////////////////////////////////////

#include <list>
#include <limits>
#include <vector>
#include <iomanip>
#include <iostream>
#include <unordered_set> 

#include "Print.h"
#include "Board.h"
#include "TicketRequest.h"


Print::Print()
{
}

Print::~Print()
{
}


// ������� ������ ������� ������ ������
void Print::printAllTickets(const std::list<TicketRequest>& tickets) {
	std::cout << std::left;
	std::cout << std::setw(3) << "#"
		<< std::setw(12) << "ID"
		<< std::setw(35) << "��������"
		<< std::setw(12) << "����"
		<< std::setw(15) << "���� ������"
		<< std::setw(20) << "����� ����������"
		<< std::setw(15) << "������" << std::endl;
	std::cout << std::string(108, '-') << std::endl;
	for (const auto& ticket : tickets) {  // ������� �� ����������� ������
		ticket.printInfo();
	}
}

// ������ ������ ���� ������ 
void Print::printAllFlights(const std::list<Board>& flights) {
	std::cout << std::left;
	std::cout << std::setw(3) << "#"
		<< std::setw(20) << "���������"
		<< std::setw(12) << "����"
		<< std::setw(15) << "����"
		<< std::setw(20) << "����� ����������"
		<< std::setw(12) << "�����������"
		<< std::setw(15) << "��������" << std::endl;

	std::cout << std::string(97, '-') << std::endl;

	int index = 1;
	for (const auto& flihgt : flights) {
		flihgt.printInfo();
	}
}


// ������� ������ �������� ������ ������
void Print::printAllTickets(const std::list<TicketRequest>& tickets, bool shortprint) {
	if (tickets.size() == 0)
	{
		std::cout << "\n" << "*������ ������ ����*";
		return;
	}
	if (shortprint)
	{
		for (const auto& ticket : tickets) {  // ������� �� ����������� ������
			std::cout << " " << std::endl << "# " << ticket.getId() << " " << ticket.getPassengerName();

		}
		std::cout << std::endl;
	}
}

// ������ ������ �� id
void Print::printBy(const std::vector<int>& ids, const std::list<TicketRequest>& tickets) {
	if (ids.empty()) {
		std::cout << "\n" << " *���������� �� �������*\n";
		return;
	}

	std::unordered_set<int> id_set(ids.begin(), ids.end());
	for (const auto& ticket : tickets) {
		if (id_set.count(ticket.getId())) {
			ticket.printInfo();
		}
	}
}

// ������ ���������� ������������� �����
void Print::printFlightInfo(const std::list<Board>& flights) {

	std::string selectedFlight;
	std::string selectedDate;
	std::cout << "������� ����� ����� ��� ������ ����������: ";
	std::cin >> selectedFlight;
	std::cout << "������� ���� �����: ";
	std::cin >> selectedDate;

	if (flights.empty()) {
		std::cout << "\n������ ������ ����!" << std::endl;
		return;
	}

	bool found = false;
	std::cout << std::endl<< std::setw(3) << "#"
		<< std::setw(20) << "���������"
		<< std::setw(12) << "����"
		<< std::setw(15) << "����"
		<< std::setw(20) << "����� ����������"
		<< std::setw(12) << "�����������"
		<< std::setw(15) << "��������" << std::endl;
	std::cout << std::string(97, '-') << std::endl;
	for (auto it = flights.begin(); it != flights.end(); ++it) {
		if (it->getFlightNumber() == selectedFlight &&
			it->getDepartureDate() == selectedDate) {

			it->printInfo();
			it->printPassengersList();
			found = true;
			break;
		}
	}

	if (!found) {
		std::cout << "\n ���� � ������� \"" << selectedFlight << "\" �� ��������� ���� �� ������." << std::endl;
	}

}