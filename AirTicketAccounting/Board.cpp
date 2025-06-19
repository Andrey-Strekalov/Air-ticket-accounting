/////////////////////////////////////////////
////////////      Board.cpp    //////////////
/////////////////////////////////////////////


#include <list>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "Board.h"
#include "TicketRequest.h"


Board::Board() {}
Board::~Board() {}

// ���������� ��������
void Board::setAircraftNumber(const std::string& value) { aircraftNumber = value; }
void Board::setAvailableSeats(int value) { availableSeats = value; }
void Board::setCapacity(int value) {
	if (value < 0) { throw std::invalid_argument("����������� �� ����� ���� �������������"); }
	capacity = value;
	calculateAvailableSeats();
}


// ���������� ��������
const std::list<TicketRequest>& Board::getPassengers() const { return passengers; }
std::string Board::getAircraftNumber() const { return aircraftNumber; }
int Board::getAvailableSeats() const { return availableSeats; }
int Board::getCapacity() const { return capacity; }



// ���������� ������� ������
void Board::addPassenger(const TicketRequest& ticket) { // ���������� ��������� � ������
	if (ticket.getFlightNumber() != flightNumber) {
		throw std::invalid_argument("����� ����� ��������� �� ��������� � ������");
	}
	if (availableSeats <= 0) {
		throw std::runtime_error("��� ��������� ����");
	}
	passengers.push_back(ticket);
	calculateAvailableSeats();
}

void Board::calculateAvailableSeats() { // ���������� ���������� ��������� ����
	availableSeats = capacity - static_cast<int>(passengers.size());
	if (availableSeats < 0) {
		availableSeats = 0;
	}
}



void Board::printInfo() const {
	 // ����� ���������� � �����
		std::cout << std::left;
		std::cout << std::setw(3) << "#"
			<< std::setw(20) << aircraftNumber
			<< std::setw(12) << flightNumber
			<< std::setw(15) << departureDate
			<< std::setw(20) << destination
			<< std::setw(12) << capacity
			<< std::setw(15) << availableSeats << std::endl;
	
}

void Board::printPassengersList() const { // ����� ������ ����������
	std::cout << std::endl << "� � � � � �    � � � � � � � � � �: " << std::endl;
	std::cout << std::left;
	std::cout << std::setw(3) << "#"
		<< std::setw(12) << "ID"
		<< std::setw(35) << "��������"
		<< std::setw(15) << "������" << std::endl;
	std::cout << std::string(58, '-') << std::endl;

	for (auto& passenger : passengers)
	{
		std::cout << std::left;
		std::cout << std::setw(3) << "#"
			<< std::setw(12) << passenger.getId()
			<< std::setw(35) << passenger.getPassengerName()
			<< std::setw(15) << passenger.getStatus() << std::endl;
	}
}

void Board::saveToFile(const std::list<Board>& flights,
	const std::string& filename) { // ���������� ������ � ����
	std::ofstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("���������� ������� ���� ��� ������!");
	}

	for (const auto& flight : flights) {
		file << flight.aircraftNumber << "|"
			<< flight.flightNumber << "|"
			<< flight.departureDate << "|"
			<< flight.destination << "|"
			<< flight.capacity << "|"
			<< flight.availableSeats << "|" << "\n";
	}

}

std::list<Board> Board::loadFromFile(const std::string& filename) { // �������� ������
	std::list<Board> flights;
	std::ifstream file(filename);

	if (!file.is_open()) {
		throw std::runtime_error("���������� ������� ���� ��� ������!");
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		Board flight;
		std::string field;

		// ������ ����
		std::getline(iss, field, '|');
		flight.setAircraftNumber(field);

		std::getline(iss, field, '|');
		flight.setFlightNumber(field);

		std::getline(iss, field, '|');
		flight.setDepartureDate(field);

		std::getline(iss, field, '|');
		flight.setDestination(field);

		std::getline(iss, field, '|');
		flight.setCapacity(std::stoi(field));

		std::getline(iss, field);
		flight.setAvailableSeats(std::stoi(field));

		flights.push_back(flight);


	}

	return flights;
}


// ����������� ������ ���������� (�������� � ���� � ������� addPassenger())
void Board::assignPassengers(std::list<Board>& flights, std::list<TicketRequest>& tickets) {

	for (auto& flight : flights) {
		flight.passengers.clear();
		for (auto& ticket : tickets) {
			if (ticket.getFlightNumber() == flight.getFlightNumber() &&
				ticket.getDepartureDate() == flight.getDepartureDate()) {
				try {
					flight.addPassenger(ticket);
				}
				catch (...) {
					// ��������� ������
				}
			}
		}
	}
}


// ������� ����������� ��������� �� ����
void Board::flightChekIn(Board* flight) {

	int capacity;
	std::string str_input;

	std::cout << "������� ����� ��������� (NN-000): ";
	getline(std::cin >> std::ws, str_input);
	flight->setAircraftNumber(str_input);

	std::cout << "������� ����� �����: ";
	getline(std::cin >> std::ws, str_input);
	flight->setFlightNumber(str_input);

	std::cout << "������� ����� ����������: ";
	getline(std::cin >> std::ws, str_input);
	flight->setDestination(str_input);

	std::cout << "����������� �����: ";
	std::cin >> capacity;
	flight->setCapacity(capacity);
	flight->calculateAvailableSeats();

	std::cout << "���� ������ (��.��.����): ";
	std::cin >> str_input;
	flight->setDepartureDate(str_input);

	std::cout << std::endl;
	std::cout << "=====================================================" << std::endl;
	std::cout << "***  ����� " << flight->getAircraftNumber() << " ���������������� �� ���� "
		<< flight->getFlightNumber() << "  ***\n" << "���� ������ "
		<< flight->getDepartureDate() << std::endl;
	std::cout << "=====================================================";


}