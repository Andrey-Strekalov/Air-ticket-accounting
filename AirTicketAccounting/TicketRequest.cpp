#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<list>
#include "TicketRequest.h"

TicketRequest::TicketRequest()
{
}

TicketRequest::~TicketRequest()
{
}

// ������� ������
void TicketRequest::setId(int value) { id = value; }
void TicketRequest::setPassengerName(std::string name) { passengerName = name; }
void TicketRequest::setFlightNumber(std::string fl_num) { flightNumber = fl_num; };
void TicketRequest::setDepartureDate(std::string date) { departurDate = date; }
void TicketRequest::setDestination(std::string value) { destination = value; }
void TicketRequest::setStatus(std::string value) { status = value; }

// ������� ������
int TicketRequest::getId() const { return id; }
std::string TicketRequest::getPassengerName() const { return passengerName; }
std::string TicketRequest::getFlightNumber()const { return flightNumber; }
std::string TicketRequest::getDepartureDate() const { return departurDate; }
std::string TicketRequest::getDestination()const { return  destination; }
std::string TicketRequest::getStatus()const { return  status; }

// ��������� ������

void TicketRequest::printTicket() const { // ������ �������
	std::cout << "\n" << std::endl;
	std::cout << "������ �" << id << std::endl;
	std::cout << "���� �" << flightNumber << std::endl;
	std::cout << "��������: " << passengerName << std::endl;
	std::cout << "���� ������: " << departurDate << std::endl;
	std::cout << "����� ����������: " << destination << std::endl;
	std::cout << "������ ������: " << status << std::endl;
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
			<< ticket.departurDate << "|"
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
		std::istringstream iss(line);
		TicketRequest ticket;
		std::string field;

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