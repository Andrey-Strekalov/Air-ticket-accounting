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

// реализация сеттеров
void Board::setAircraftNumber(const std::string& value) { aircraftNumber = value; }
void Board::setAvailableSeats(int value) { availableSeats = value; }
void Board::setCapacity(int value) {
	if (value < 0) { throw std::invalid_argument("Вместимость не может быть отрицательной"); }
	capacity = value;
	calculateAvailableSeats();
}


// реализация геттеров
const std::list<TicketRequest>& Board::getPassengers() const { return passengers; }
std::string Board::getAircraftNumber() const { return aircraftNumber; }
int Board::getAvailableSeats() const { return availableSeats; }
int Board::getCapacity() const { return capacity; }



// Реализация методов класса
void Board::addPassenger(const TicketRequest& ticket) { // добавление пассажира в список
	if (ticket.getFlightNumber() != flightNumber) {
		throw std::invalid_argument("Номер рейса пассажира не совпадает с бортом");
	}
	if (availableSeats <= 0) {
		throw std::runtime_error("Нет свободных мест");
	}
	passengers.push_back(ticket);
	calculateAvailableSeats();
}

void Board::calculateAvailableSeats() { // вычисление количества свободных мест
	availableSeats = capacity - static_cast<int>(passengers.size());
	if (availableSeats < 0) {
		availableSeats = 0;
	}
}



void Board::printInfo() const {
	 // вывод информации о рейсе
		std::cout << std::left;
		std::cout << std::setw(3) << "#"
			<< std::setw(20) << aircraftNumber
			<< std::setw(12) << flightNumber
			<< std::setw(15) << departureDate
			<< std::setw(20) << destination
			<< std::setw(12) << capacity
			<< std::setw(15) << availableSeats << std::endl;
	
}

void Board::printPassengersList() const { // вывод списка пассажиров
	std::cout << std::endl << "С п и с о к    п а с с а ж и р о в: " << std::endl;
	std::cout << std::left;
	std::cout << std::setw(3) << "#"
		<< std::setw(12) << "ID"
		<< std::setw(35) << "Пассажир"
		<< std::setw(15) << "Статус" << std::endl;
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
	const std::string& filename) { // сохранение данных в файл
	std::ofstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Невозможно открыть файл для записи!");
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

std::list<Board> Board::loadFromFile(const std::string& filename) { // загрузка данных
	std::list<Board> flights;
	std::ifstream file(filename);

	if (!file.is_open()) {
		throw std::runtime_error("Невозможно открыть файл для чтения!");
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		Board flight;
		std::string field;

		// Парсим поля
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


// составление списка пассажиров (работает в паре с методом addPassenger())
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
					// Обработка ошибок
				}
			}
		}
	}
}


// функция регистрации авиасудна на рейс
void Board::flightChekIn(Board* flight) {

	int capacity;
	std::string str_input;

	std::cout << "Введите номер авиасудна (NN-000): ";
	getline(std::cin >> std::ws, str_input);
	flight->setAircraftNumber(str_input);

	std::cout << "Введите номер рейса: ";
	getline(std::cin >> std::ws, str_input);
	flight->setFlightNumber(str_input);

	std::cout << "Введите пункт назначения: ";
	getline(std::cin >> std::ws, str_input);
	flight->setDestination(str_input);

	std::cout << "Вместимость судна: ";
	std::cin >> capacity;
	flight->setCapacity(capacity);
	flight->calculateAvailableSeats();

	std::cout << "Дата вылета (дд.мм.гггг): ";
	std::cin >> str_input;
	flight->setDepartureDate(str_input);

	std::cout << std::endl;
	std::cout << "=====================================================" << std::endl;
	std::cout << "***  Судно " << flight->getAircraftNumber() << " зарегистрировано на рейс "
		<< flight->getFlightNumber() << "  ***\n" << "Дата вылета "
		<< flight->getDepartureDate() << std::endl;
	std::cout << "=====================================================";


}