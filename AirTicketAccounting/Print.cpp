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


// функция вывода полного списка заявок
void Print::printAllTickets(const std::list<TicketRequest>& tickets) {
	std::cout << std::left;
	std::cout << std::setw(3) << "#"
		<< std::setw(12) << "ID"
		<< std::setw(35) << "Пассажир"
		<< std::setw(12) << "Рейс"
		<< std::setw(15) << "Дата вылета"
		<< std::setw(20) << "Пункт назначения"
		<< std::setw(15) << "Статус" << std::endl;
	std::cout << std::string(108, '-') << std::endl;
	for (const auto& ticket : tickets) {  // Перебор по константной ссылке
		ticket.printInfo();
	}
}

// печать списка всех рейсов 
void Print::printAllFlights(const std::list<Board>& flights) {
	std::cout << std::left;
	std::cout << std::setw(3) << "#"
		<< std::setw(20) << "Авиасудно"
		<< std::setw(12) << "Рейс"
		<< std::setw(15) << "Дата"
		<< std::setw(20) << "Пункт назначения"
		<< std::setw(12) << "Вместимость"
		<< std::setw(15) << "Свободно" << std::endl;

	std::cout << std::string(97, '-') << std::endl;

	int index = 1;
	for (const auto& flihgt : flights) {
		flihgt.printInfo();
	}
}


// функция вывода краткого списка заявок
void Print::printAllTickets(const std::list<TicketRequest>& tickets, bool shortprint) {
	if (tickets.size() == 0)
	{
		std::cout << "\n" << "*Список заявок пуст*";
		return;
	}
	if (shortprint)
	{
		for (const auto& ticket : tickets) {  // Перебор по константной ссылке
			std::cout << " " << std::endl << "# " << ticket.getId() << " " << ticket.getPassengerName();

		}
		std::cout << std::endl;
	}
}

// печать заявок по id
void Print::printBy(const std::vector<int>& ids, const std::list<TicketRequest>& tickets) {
	if (ids.empty()) {
		std::cout << "\n" << " *Совпадений не найдено*\n";
		return;
	}

	std::unordered_set<int> id_set(ids.begin(), ids.end());
	for (const auto& ticket : tickets) {
		if (id_set.count(ticket.getId())) {
			ticket.printInfo();
		}
	}
}

// печать информации определенного рейса
void Print::printFlightInfo(const std::list<Board>& flights) {

	std::string selectedFlight;
	std::string selectedDate;
	std::cout << "Введите номер рейса для вывода информации: ";
	std::cin >> selectedFlight;
	std::cout << "Введите дату рейса: ";
	std::cin >> selectedDate;

	if (flights.empty()) {
		std::cout << "\nСписок рейсов пуст!" << std::endl;
		return;
	}

	bool found = false;
	std::cout << std::endl<< std::setw(3) << "#"
		<< std::setw(20) << "Авиасудно"
		<< std::setw(12) << "Рейс"
		<< std::setw(15) << "Дата"
		<< std::setw(20) << "Пункт назначения"
		<< std::setw(12) << "Вместимость"
		<< std::setw(15) << "Свободно" << std::endl;
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
		std::cout << "\n Рейс с номером \"" << selectedFlight << "\" на указанную дату не найден." << std::endl;
	}

}