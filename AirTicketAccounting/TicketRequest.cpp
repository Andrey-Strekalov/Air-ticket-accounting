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

// Сеттеры класса
void TicketRequest::setId(int value) { id = value; }
void TicketRequest::setStatus(std::string value) { status = value; }
void TicketRequest::setPassengerName(std::string name) { passengerName = name; }

// Геттеры класса
int TicketRequest::getId() const { return id; }
std::string TicketRequest::getStatus()const { return  status; }
std::string TicketRequest::getPassengerName() const { return passengerName; }


// Остальные методы
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


		// Парсим поля
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
	std::cout << "Введите id заявки: ";
	std::cin >> id;

	// Получаем итератор на элемент списка
	auto it = getTicketRequestById(tickets, id);

	if (it == tickets.end()) {
		std::cout << "Заявка не найдена!\n";
		return;
	}

	// Работаем с исходным объектом через итератор (ссылку)
	it->printTicket();

	std::string term;
	std::cout << "\n" << "Это ваша заявка (y/n)? ";
	std::cin >> term;

	if (term == "y") {
		int point;
		do {
			point = Menu::menuInRequestWork(id);
			switch (point) {
			case 1: {
				std::string new_status;
				std::cout << "Введите новый статус: ";
				std::getline(std::cin >> std::ws, new_status);

				// Модифицируем исходный объект через итератор
				it->setStatus(new_status);
				std::cout << "Статус заявки #" << id << " изменен. Текущий статус: " << it->getStatus() << "\n";
				break;
			}
			case 2: {
				// Удаляем заявку из списка через итератор
				std::string corr;
				std::cout << "Вы уверены, что хотите удалить заявку (y/n)?";
				std::cin >> corr;
				if (corr == "y")
				{
					tickets.erase(it);
					std::cout << "\n" << "*Заявка удалена!*\n";
					sortList(tickets);
					return;
				}
				else
				{
					std::cout << "*Удаление заявки отменено*";
					break;
				}

			}
			case 3:
				break;
			default:
				std::cout << "Некорректный ввод!\n";
				break;
			}
		} while (point != 3);
	}
}

// Фунцкия возврата объекта по id
std::list<TicketRequest>::iterator
TicketRequest::getTicketRequestById(std::list<TicketRequest>& tickets, int id) {
	for (auto it = tickets.begin(); it != tickets.end(); ++it) {
		if (it->getId() == id) {
			return it;
		}
	}
	return tickets.end();
}


// сортировка контейнера заявок по алфавиту
void TicketRequest::sortList(std::list<TicketRequest>& container) {
	container.sort([](const TicketRequest& a, const TicketRequest& b) {
		return a.getPassengerName() < b.getPassengerName();
		});
}


void TicketRequest::createTicketRequest(TicketRequest* ticket, std::list<Board>& flights) {

	// Выбор рейса из списка
	std::cout << "\nДоступные рейсы:\n" << std::endl;
	for (const auto& f : flights) {

		std::cout << std::left << std::setw(12) << f.getFlightNumber()
			<< f.getDepartureDate()
			<< " (Свободно мест: " << f.getAvailableSeats() << ")\n";
	}
	std::cout << std::endl;

	if (flights.size() != 0)
	{
		std::string selectedFlight;
		std::string selectedDate;
		std::cout << "Введите номер рейса: ";
		std::cin >> selectedFlight;
		std::cout << "Введите дату: ";
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
					"\n Рейс с номером \"" + selectedFlight +
					"\" на указанную дату не найден.");
			}

			selected_board = &(*it);

			ticket->setFlightNumber(selectedFlight);
			ticket->setDepartureDate(selected_board->getDepartureDate());
			ticket->setDestination(selected_board->getDestination());
			selected_board->addPassenger(*ticket);

			int id = time(nullptr);
			std::string name;
			ticket->setId(id);

			std::cout << "Введите ФИО пассажира: ";
			getline(std::cin >> std::ws, name);
			ticket->setPassengerName(name);

			ticket->setStatus("В обработке");
			selected_board->calculateAvailableSeats();

			std::cout << std::endl;
			std::cout << "================================================" << std::endl;
			std::cout << "***  Заявка " << id << " успешно создана  ***" << std::endl;
			std::cout << "================================================";
		}
		catch (const std::exception& e) {
			std::cerr << "Ошибка: " << e.what() << "\n";
			return;
		}

	}
	else
	{
		std::cout << "*** Список рейсов пуст ***";
	}
};
