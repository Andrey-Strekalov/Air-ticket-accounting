/////////////////////////////////////////////
////////////      Main.cpp     //////////////
/////////////////////////////////////////////


//..................... подключение библиотек и заголовочных файлов ..................// 

#include <iostream>
#include <iomanip>
#include <string>
#include <list> 

// заголовочные файлы
#include "TicketRequest.h"; // с классом заявки на билет
#include "FlightInfo.h" // общий класс 
#include "Board.h"  // класс борта 
#include "Print.h" // класс вывода информации об объектах 
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
		case 3: // выход
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
// критерий поиска передается в параметре criteria, по значению которой выбирается определенный case
std::vector<int> searchRequestBy(int criteria, const std::list<TicketRequest>& tickets) {
	std::vector<int> ids;
	if (tickets.empty()) {
		std::cout << "Список заявок пуст!\n";
		return ids;
	}

	// Строка значения для поиска 
	std::string search_string;
	int search_unit = 0;


	switch (criteria) {
	case 1: // По имени
		std::cout << "Введите ФИО пассажира: ";
		std::getline(std::cin >> std::ws, search_string);
		break;
	case 2: // По номеру рейса
		std::cout << "Введите номер рейса (РР-111): ";
		std::getline(std::cin >> std::ws, search_string);
		break;
	case 3: // По ID
		std::cout << "Введите ID (000000000): ";
		std::cin >> search_unit;
		std::cin.ignore(); // Очистка буфера
		break;
	case 4: // По пункту назначения
		std::cout << "Введите пункт назначения: ";
		std::getline(std::cin >> std::ws, search_string);
		break;
	case 5: // По дате вылета
		std::cout << "Введите дату вылета (дд.мм.гггг): ";
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

		std::vector<int> ids = searchRequestBy(choice, tickets);// ищем заявки
		if (!ids.empty()) { // если возвращается непустой вектор
			std::cout << "\nНайдены заявки:" << std::endl;
			std::cout << std::left;
			std::cout << std::setw(3) << "#" // печатаем список
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

	Board flight; // создаем объект класса Board
	TicketRequest ticket; // создаем объект класса TicketRequest

	int point; // переменная для выбора позиции меню
	do // цикл работы в меню
	{
		point = Menu::ticketMenu();

		switch (point) // переключатель основного меню операций с заявками
		{
		case 1: // создать заявку
			TicketRequest::createTicketRequest(&ticket, flights);
			if (ticket.getId() != 0)
			{
				tickets.push_back(ticket);
			}
			TicketRequest::sortList(tickets);
			TicketRequest::saveToFile(tickets, "Requests.dat");
			Board::assignPassengers(flights, tickets);
			break;
		case 2: // просмотр всех заявок
			Print::printAllTickets(tickets); 
			break;

		case 3: { // поиск заявок
			searchRequestsBlock(tickets);
			break;
		}
		case 4: { // работа с заявкой (удаление и смена статуса) 
			TicketRequest::workInRequest(tickets);
			TicketRequest::saveToFile(tickets, "Requests.dat");
			Board::saveToFile(flights, "Flights.dat");
			break;
		}
		case 5: //  выход, пересчет свободных мест и обновление списка пассажиров
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

	Board flight; // создаем объект класса Board
	TicketRequest ticket; // создаем объект класса TicketRequest

	int point; // переменная для выбора позиции меню
	do // цикл работы в меню
	{
		point = Menu::flightMenu(); 
		switch (point) // переключатель основного меню операций с заявками
		{
		case 1: { // регистрация рейса
			Board::flightChekIn(&flight);
			flights.push_back(flight);
			Board::saveToFile(flights, "Flights.dat");
			break;
		}
		case 2: { // печать всех рейсов
			Print::printAllFlights(flights);
			break;
		}

		case 3: Print::printFlightInfo(flights); // вывод информации о рейсе
		case 4: { // выход и сохранение в файл
			Board::saveToFile(flights, "Flights.dat"); 
		}
			  break;
		default:
			std::cout << "Неккоректный ввод! Попробуйте еще раз.";
			break;
		}
	} while (point != 4);
}
