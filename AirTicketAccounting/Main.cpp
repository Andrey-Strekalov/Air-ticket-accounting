/////////////////////////////////////////////
//////////// Main.cpp ///////////////////////
/////////////////////////////////////////////

#include <iostream>
#include <list>
#include <ctime>
#include <Windows.h> // для использования SetConsoleCP и 
#include "TicketRequest.h";

int createId();
TicketRequest createTicketRequest(TicketRequest* ticket);
void printAllTickets(const std::list<TicketRequest>& tickets);
int menu();

int main()
{   // меняем кодировку консоли и устанавливаем локаль для возможности рускоязычного ввода и вывода
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// двусвязный контейнер list tickets для хранения заявок 
	std::list<TicketRequest> tickets{};
	TicketRequest ticket;


	/*createTicketRequest(&ticket);
	tickets.push_back(ticket);
	printTicketRequest(&ticket);*/
	int point;
	do
	{
		point = menu();
		switch (point)
		{
		case 1:
			createTicketRequest(&ticket);
			tickets.push_back(ticket);
			break;
		case 2: printAllTickets(tickets);
			break;
		case 5: break;
		default:
			std::cout << "Неккоректный ввод! Попробуйте еще раз)";
			break;
		}
	} while (point != 5);
	return 0;
}


int createId() { return time(nullptr); }
int menu() {
	int point;
	while (true) {
		std::cout << "\n";
		std::cout << "\n----------------- Главное меню -----------------\n" 
			<< "\n" 
			<< "1 - Заполнить заявку \t2 - Посмотреть заявки\n" 
			/*<< "2 - Переместить\t\t4 - Определить отношение включения\n"*/
			<< "\t\t5 - Выход\n" 
			<< "\n" 
			<< "________________________________________________" << std::endl
			<< "Выберите пункт: ";


		if (std::cin >> point && point >= 1 && point <= 5) {
			return point;
		}
		std::cin.clear(); // Сброс флага ошибки
		std::cin.ignore(10000, '\n'); // Очистка буфера
		std::cout << "Ошибка! Введите число от 1 до 5!\n";
	}
}

TicketRequest createTicketRequest(TicketRequest* ticket) {

	int id = createId();
	std::string name;
	std::string fl_num;
	std::string date;
	std::string to;
	std::string status;
	ticket->setId(id);

	std::cin.ignore();

	std::cout << "Введите имя пассажира ";
	getline(std::cin, name);
	ticket->setPassengerName(name);

	std::cout << "Введите дату вылета ";
	std::cin >> date;
	ticket->setDepartureDate(date);
	//std::cin.ignore();

	std::cout << "Введите номер рейса ";
	std::cin >> fl_num;
	ticket->setFlightNumber(fl_num);
	//std::cin.ignore();

	std::cout << "Введите пункт назначения ";
	std::cin >> to;
	ticket->setDestination(to);
	std::cin.ignore();

	ticket->setStatus("В обработке");

	std::cout << std::endl;
	std::cout << "================================================" << std::endl;
	std::cout << "***  Заявка " << id << " успешно создана  ***" << std::endl;
	std::cout << "================================================";

	return *ticket;
};

void printAllTickets(const std::list<TicketRequest>& tickets) {
	for (const auto& ticket : tickets) {  // Перебор по константной ссылке
		ticket.printTicket();
	}
}