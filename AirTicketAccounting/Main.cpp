/////////////////////////////////////////////
//////////// Main.cpp ///////////////////////
/////////////////////////////////////////////

#include <iostream>
#include <list>
#include <ctime>
#include <Windows.h> // для использования SetConsoleCP и 
#include "TicketRequest.h";

int createId() {
	return time(nullptr);
}


TicketRequest createTicketRequest(TicketRequest* ticket) {

	int id = createId();
	std::string name;
	std::string fl_num;
	std::string date;
	std::string to;
	std::string status;
	ticket->setId(id);

	std::cout << "Введите имя пассажира ";
	getline(std::cin, name);
	ticket->setPassengerName(name);

	std::cout << "Введите дату вылета ";
	std::cin >> date;
	ticket->setDepartureDate(date);

	std::cout << "Введите номер рейса ";
	std::cin >> fl_num;
	ticket->setFlightNumber(fl_num);

	std::cout << "Введите пункт назначения ";
	std::cin >> to;
	ticket->setDestination(to);

	ticket->setStatus("in processed");

	std::cout << std::endl;
	std::cout << "============================================";

	return *ticket;
};

void printTicketRequest(TicketRequest* ticket) {
	std::cout << "\n" << std::endl;
	std::cout << "Заявка №" << ticket->getId() << std::endl;
	std::cout << "Рейс №" << ticket->getFlightNumber() << std::endl;
	std::cout << "Пассажир: " << ticket->getPassengerName() << std::endl;
	std::cout << "Дата вылета: " << ticket->getDepartureDate() << std::endl;
	std::cout << "Пункт назначения: " << ticket->getDestination() << std::endl;
	std::cout << "Статус заявки: " << ticket->getStatus() << std::endl;
}

int main()
{
	setlocale(LC_ALL, "ru");
	// меняем кодировку консоли для возможности рускоязычного ввода
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	std::list<TicketRequest> tickets{};

	TicketRequest* ticket = new TicketRequest;

	createTicketRequest(ticket);
	//tickets.push_back(ticket);

	printTicketRequest(ticket);

	delete ticket;
	return 0;
}


