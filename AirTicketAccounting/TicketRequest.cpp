/////////////////////////////////////////////
//////////      TicketRequest.cpp    ////////
/////////////////////////////////////////////

#include<list>
#include <ctime>
#include <string>
#include <iomanip>  
#include <fstream>
#include <sstream>
#include <iostream>


#include "Menu.h"
#include "Board.h"
#include "FlightInfo.h"
#include "TicketRequest.h"

TicketRequest::TicketRequest() { id = 0; }
TicketRequest::~TicketRequest() {}

// ������� ������
void TicketRequest::setId(int value) { id = value; }
void TicketRequest::setStatus(std::string value) { status = value; }
void TicketRequest::setPassengerName(std::string name) { passengerName = name; }

// ������� ������
int TicketRequest::getId() const { return id; }
std::string TicketRequest::getStatus()const { return  status; }
std::string TicketRequest::getPassengerName() const { return passengerName; }


// ��������� ������
void TicketRequest::printTicket() const {

	std::cout << std::left;
	std::cout << std::setw(3) << "#"
		<< std::setw(12) << id
		<< std::setw(35) << passengerName
		<< std::setw(12) << flightNumber
		<< std::setw(15) << departureDate
		<< std::setw(20) << destination
		<< std::setw(15) << status << std::endl;
}

void TicketRequest::saveToFile(const std::list<TicketRequest>& tickets,
	const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Cannot open file for writing");
	}

	for (const auto& ticket : tickets) {
		file << ticket.id << "|"
			<< ticket.passengerName << "|"
			<< ticket.flightNumber << "|"
			<< ticket.departureDate << "|"
			<< ticket.destination << "|"
			<< ticket.status << "\n";
	}
}

std::list<TicketRequest> TicketRequest::loadFromFile(const std::string& filename) {
	std::list<TicketRequest> tickets;
	std::ifstream file(filename);

	if (!file.is_open()) {
		throw std::runtime_error("Cannot open file for reading");
	}

	std::string line;
	while (std::getline(file, line)) {
		TicketRequest ticket;
		std::string field;
		std::istringstream iss(line);


		// ������ ����
		std::getline(iss, field, '|');
		ticket.setId(std::stoi(field));

		std::getline(iss, field, '|');
		ticket.setPassengerName(field);

		std::getline(iss, field, '|');
		ticket.setFlightNumber(field);

		std::getline(iss, field, '|');
		ticket.setDepartureDate(field);

		std::getline(iss, field, '|');
		ticket.setDestination(field);

		std::getline(iss, field);
		ticket.setStatus(field);

		tickets.push_back(ticket);
	}

	return tickets;
}

void TicketRequest::workInRequest(std::list<TicketRequest>& tickets) {
	int id;
	std::cout << "������� id ������: ";
	std::cin >> id;

	// �������� �������� �� ������� ������
	auto it = getTicketRequestById(tickets, id);

	if (it == tickets.end()) {
		std::cout << "������ �� �������!\n";
		return;
	}

	// �������� � �������� �������� ����� �������� (������)
	it->printTicket();

	std::string term;
	std::cout << "\n" << "��� ���� ������ (y/n)? ";
	std::cin >> term;

	if (term == "y") {
		int point;
		do {
			point = Menu::menuInRequestWork(id);
			switch (point) {
			case 1: {
				std::string new_status;
				std::cout << "������� ����� ������: ";
				std::getline(std::cin >> std::ws, new_status);

				// ������������ �������� ������ ����� ��������
				it->setStatus(new_status);
				std::cout << "������ ������ #" << id << " �������. ������� ������: " << it->getStatus() << "\n";
				break;
			}
			case 2: {
				// ������� ������ �� ������ ����� ��������
				std::string corr;
				std::cout << "�� �������, ��� ������ ������� ������ (y/n)?";
				std::cin >> corr;
				if (corr == "y")
				{
					tickets.erase(it);
					std::cout << "\n" << "*������ �������!*\n";
					sortList(tickets);
					return;
				}
				else
				{
					std::cout << "*�������� ������ ��������*";
					break;
				}

			}
			case 3:
				break;
			default:
				std::cout << "������������ ����!\n";
				break;
			}
		} while (point != 3);
	}
}

// ������� �������� ������� �� id
std::list<TicketRequest>::iterator
TicketRequest::getTicketRequestById(std::list<TicketRequest>& tickets, int id) {
	for (auto it = tickets.begin(); it != tickets.end(); ++it) {
		if (it->getId() == id) {
			return it;
		}
	}
	return tickets.end();
}


// ���������� ���������� ������ �� ��������
void TicketRequest::sortList(std::list<TicketRequest>& container) {
	container.sort([](const TicketRequest& a, const TicketRequest& b) {
		return a.getPassengerName() < b.getPassengerName();
		});
}


void TicketRequest::createTicketRequest(TicketRequest* ticket, std::list<Board>& flights) {

	// ����� ����� �� ������
	std::cout << "\n��������� �����:\n" << std::endl;
	for (const auto& f : flights) {

		std::cout << std::left << std::setw(12) << f.getFlightNumber()
			<< f.getDepartureDate()
			<< " (�������� ����: " << f.getAvailableSeats() << ")\n";
	}
	std::cout << std::endl;

	if (flights.size() != 0)
	{
		std::string selectedFlight;
		std::string selectedDate;
		std::cout << "������� ����� �����: ";
		std::cin >> selectedFlight;
		std::cout << "������� ����: ";
		std::cin >> selectedDate;

		try {
			Board* selected_board = nullptr;
			auto it = std::find_if(flights.begin(), flights.end(),
				[&](const Board& b) { return
				b.getFlightNumber() == selectedFlight &&
				b.getDepartureDate() == selectedDate; });
			if (it == flights.end()) {
				std::cout << std::endl;
				throw std::runtime_error(
					"\n ���� � ������� \"" + selectedFlight +
					"\" �� ��������� ���� �� ������.");
			}

			selected_board = &(*it);

			ticket->setFlightNumber(selectedFlight);
			ticket->setDepartureDate(selected_board->getDepartureDate());
			ticket->setDestination(selected_board->getDestination());
			selected_board->addPassenger(*ticket);

			int id = time(nullptr);
			std::string name;
			ticket->setId(id);

			std::cout << "������� ��� ���������: ";
			getline(std::cin >> std::ws, name);
			ticket->setPassengerName(name);

			ticket->setStatus("� ���������");
			selected_board->calculateAvailableSeats();

			std::cout << std::endl;
			std::cout << "================================================" << std::endl;
			std::cout << "***  ������ " << id << " ������� �������  ***" << std::endl;
			std::cout << "================================================";
		}
		catch (const std::exception& e) {
			std::cerr << "������: " << e.what() << "\n";
			return;
		}

	}
	else
	{
		std::cout << "*** ������ ������ ���� ***";
	}
};
