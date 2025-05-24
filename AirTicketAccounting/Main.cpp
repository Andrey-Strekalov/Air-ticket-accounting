/////////////////////////////////////////////
////////////      Main.cpp     //////////////
/////////////////////////////////////////////


//..................... подключение библиотек и заголовочных файлов ..................// 
#include <unordered_set> 
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <list> 

// заголовочные файлы
#include "TicketRequest.h"; // с классом заявки на билет
#include "FlightInfo.h" // общий класс 
#include "Board.h" // класс борта 
#include "Print.h"// класс вывода информации об объектах 
#include "Menu.h" // класс с меню





//.......................... прототипы используемых функций ..........................// 



void ticketOperations(std::list<TicketRequest>& tickets, std::list<Board>& flights); // функция операций с заявками на билеты
void flightOperations(std::list<TicketRequest>& tickets, std::list<Board>& flights); // функция операций с рейсами


// функция поиска заявки по введенному полю (возвращает вектор ) поиск заявки по введенному полю
std::vector <int> searchRequestBy(int value, const std::list<TicketRequest>& tickets); 

// блок поиска заявок по различным полям (блок фильтров)
void searchRequestsBlock(std::list<TicketRequest>& tickets);





//................................. main функция ....................................// 


int main()
{


	// меняем кодировку консоли для возможности рускоязычного ввода и вывода
	system("chcp 1251 > nul");
	system("color F0");

	// двусвязный контейнер list tickets для хранения заявок 
	std::list<TicketRequest> tickets{};

	// двусвязный контейнер list flights для хранения рейсов
	std::list<Board> flights{};


	// загрузка данных из файлов
	try {
		std::cout << "Загрузка рейсов...";
		tickets = TicketRequest::loadFromFile("Requests.dat"); // загрузка заявок 
		std::cout << "Рейсы загружены." << std::endl;
		std::cout << "Загрузка заявок...";
		flights = Board::loadFromFile("Flights.dat"); // загрузка рейсов
		std::cout << "Заявки загружены." << std::endl;
		Board::assignPassengers(flights, tickets); // добавление пассажиров к рейсам
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}


	int point; // переменная для выбора позиции меню
	do // цикл работы в меню
	{
		point = Menu::mainMenu();
		switch (point)
		{
		case 1: { // кейс операций с заявками
			ticketOperations(tickets, flights);
			break;
		}
		case 2: { // кейс операций с рейсами
			flightOperations(tickets, flights);
			break;
		}
		case 3:
			break;
		default:
			std::cout << "Неккоректный ввод! Попробуйте еще раз)";
			break;
		}
	} while (point != 3);

	return 0;
}





//................................ реализация функций ..................................// 



// поиск заявки по имени пассажира, возвращает вектор id найденных по запросу пользователя заявок
std::vector<int> searchRequestBy(int criteria, const std::list<TicketRequest>& tickets) {
	std::vector<int> ids;
	if (tickets.empty()) {
		std::cout << "Список заявок пуст!\n";
		return ids;
	}

	// Ввод значения для поиска 
	std::string search_string;
	int search_unit = 0;


	switch (criteria) {
	case 1: // По имени
		std::cout << "Введите имя: ";
		std::getline(std::cin >> std::ws, search_string);
		break;
	case 2: // По номеру рейса
		std::cout << "Введите номер рейса: ";
		std::getline(std::cin >> std::ws, search_string);
		break;
	case 3: // По ID
		std::cout << "Введите ID: ";
		std::cin >> search_unit;
		std::cin.ignore(); // Очистка буфера
		break;
	case 4: // По пункту назначения
		std::cout << "Введите пункт назначения: ";
		std::getline(std::cin >> std::ws, search_string);
		break;
	case 5: // По дате вылета
		std::cout << "Введите дату вылета: ";
		std::getline(std::cin >> std::ws, search_string);
		break;
	default:
		return ids;
	}

	// Поиск по всем заявкам
	for (const auto& ticket : tickets) {
		bool match = false;
		switch (criteria) {
		case 1: match = ticket.getPassengerName().find(search_string) != std::string::npos; break;
		case 2: match = ticket.getFlightNumber() == search_string; break;
		case 3: match = ticket.getId() == search_unit; break;
		case 4: match = ticket.getDestination().find(search_string) != std::string::npos; break;
		case 5: match = ticket.getDepartureDate() == search_string; break;
		}
		if (match) ids.push_back(ticket.getId());
	}

	return ids;
}


// блок поиска заявок (блок фильтров)
void searchRequestsBlock(std::list<TicketRequest>& tickets) {
	int choice;
	do {
		choice = Menu::menuInSearchBlock();
		if (choice == 6) break; // Выход

		std::vector<int> ids = searchRequestBy(choice, tickets);
		if (!ids.empty()) {
			std::cout << "\nНайдены заявки:" << std::endl;
			std::cout << std::left;
			std::cout << std::setw(3) << "#"
				<< std::setw(12) << "ID"
				<< std::setw(35) << "Пассажир"
				<< std::setw(12) << "Рейс"
				<< std::setw(15) << "Дата вылета"
				<< std::setw(20) << "Пункт назначения"
				<< std::setw(15) << "Статус" << std::endl;
			std::cout << std::string(108, '-') << std::endl;
			Print::printBy(ids, tickets);
		}
		else {
			std::cout << "Совпадений не найдено.\n";
		}
	} while (true);
}



// функция операций с заявками на билеты
void ticketOperations(std::list<TicketRequest>& tickets, std::list<Board>& flights) {

	Board flight;
	TicketRequest ticket;

	int point; // переменная для выбора позиции меню
	do // цикл работы в меню
	{
		point = Menu::ticketMenu();
		switch (point)
		{
		case 1:
			TicketRequest::createTicketRequest(&ticket, flights);
			if (ticket.getId() != 0)
			{
				tickets.push_back(ticket);
			}
			TicketRequest::sortList(tickets);
			TicketRequest::saveToFile(tickets, "Requests.dat");
			Board::assignPassengers(flights, tickets);
			break;
		case 2: Print::printAllTickets(tickets);
			break;

		case 3: {
			searchRequestsBlock(tickets);
			break;
		}
		case 4: {
			TicketRequest::workInRequest(tickets);
			TicketRequest::saveToFile(tickets, "Requests.dat");
			Board::saveToFile(flights, "Flights.dat");
			break;
		}
		case 5:
			tickets = TicketRequest::loadFromFile("Requests.dat");
			flights = Board::loadFromFile("Flights.dat");
			Board::assignPassengers(flights, tickets);
			break;
		default:
			std::cout << "Неккоректный ввод! Попробуйте еще раз.";
			break;
		}
	} while (point != 5);
}


// функция операций с рейсами
void flightOperations(std::list<TicketRequest>& tickets, std::list<Board>& flights) {

	Board flight;
	TicketRequest ticket;

	int point; // переменная для выбора позиции меню
	do // цикл работы в меню
	{
		point = Menu::flightMenu();
		switch (point)
		{
		case 1: {
			Board::flightChekIn(&flight);
			flights.push_back(flight);
			Board::saveToFile(flights, "Flights.dat");
			break;
		}
		case 2: {
			Print::printAllFlights(flights);
			break;
		}

		case 3: Print::printFlightInfo(flights);
		case 4: {
			Board::saveToFile(flights, "Flights.dat");
		}
			  break;
		default:
			std::cout << "Неккоректный ввод! Попробуйте еще раз.";
			break;
		}
	} while (point != 4);
}
