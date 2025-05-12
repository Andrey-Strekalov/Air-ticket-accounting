/////////////////////////////////////////////
////////////      Main.cpp     //////////////
/////////////////////////////////////////////


//..................... подключение библиотек и заголовочных файлов ..................// 
#include <unordered_set>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <ctime>
#include <list> 

// заголовочные файлы
#include "TicketRequest.h"; // с классом заявки на билет




//.......................... прототипы используемых функций ..........................// 

// функции меню
int menu(); // главное меню программы
int menuInRequestWork(int id); // меню работы с заявкой

// Функция получения для создания новых заявок
int createId(); // получение индивидуального id
TicketRequest createTicketRequest(TicketRequest* ticket); // создание заявки

// фунцкии полной и сокращенной информации по заявкам с перегрузкой по параметрам
void printAllTickets(const std::list<TicketRequest>& tickets);
void printAllTickets(const std::list<TicketRequest>& tickets, bool shortprint);

// функция работы с заявкой, удаление и изменение статуса
void workInRequest(std::list<TicketRequest>& tickets);

// функции поиска и получения заявки
std::vector <int> searchByName(const std::list<TicketRequest>& tickets);
TicketRequest getTicketRequestById(const std::list<TicketRequest>& tickets, int id);

// Вывод списка заявок 
void printBy(const std::vector<int>& ids, const std::list<TicketRequest>& tickets);
// добавятся перегрузки этой фунцкии по параметрам, будет использовано для фильтров.





//................................. main функция ....................................// 


int main()
{
	// меняем кодировку консоли для возможности рускоязычного ввода и вывода
	system("chcp 1251 > nul");

	// двусвязный контейнер list tickets для хранения заявок 
	std::list<TicketRequest> tickets{};
	TicketRequest ticket;

	int point; // переменная для выбора позиции меню
	do // цикл работы в меню
	{
		point = menu();
		switch (point)
		{
		case 1:
			createTicketRequest(&ticket);
			tickets.push_back(ticket);
			break;
		case 2: printAllTickets(tickets, true);
			break;

		case 3: {
			const std::vector <int> ids = searchByName(tickets);
			printBy(ids, tickets);
			break;
		}
		case 4: {
			workInRequest(tickets);

			break;
		}

		case 5: break;
		default:
			std::cout << "Неккоректный ввод! Попробуйте еще раз)";
			break;
		}
	} while (point != 5);
	return 0;
}





//................................ реализация функций ..................................// 


int createId() { return time(nullptr); } // получение id для новой заявки 

int menu() { // функция главного меню программы
	int point;
	while (true) {
		std::cout << "\n" << "\n----------------- Главное меню -----------------\n"
			<< "\n"
			<< " 1 - Заполнить заявку \t2 - Посмотреть заявки\n"
			<< " 3 - Найти заявку\t4 - Работа с заявкой         \n"
			<< "\t\t5 - Выход\n"
			<< "\n"
			<< "________________________________________________" << std::endl
			<< "Выберите пункт: ";

		// проверка на валдиность ввода 
		if (std::cin >> point && point >= 1 && point <= 5) {
			return point;
		}
		std::cin.clear(); // Сброс флага ошибки
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Ошибка! Введите число от 1 до 5!\n";
	}
}

// функция создания заявки
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

	std::cout << "Введите номер рейса ";
	std::cin >> fl_num;
	ticket->setFlightNumber(fl_num);

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

// функция вывода полного списка заявок
void printAllTickets(const std::list<TicketRequest>& tickets) {
	for (const auto& ticket : tickets) {  // Перебор по константной ссылке
		ticket.printTicket();
	}
}

// функция вывода краткого списка заявок
void printAllTickets(const std::list<TicketRequest>& tickets, bool shortprint) {
	if (tickets.size() == 0)
	{
		std::cout << "\n" << "*Список заявок пуст*";
		return;
	}
	if (shortprint)
	{
		for (const auto& ticket : tickets) {  // Перебор по константной ссылке
			std::cout << " " << std::endl << ticket.getId() << " " << ticket.getPassengerName() << std::endl;
		}
	}
}

// поиск заявки по имени пассажира
std::vector<int> searchByName(const std::list<TicketRequest>& tickets) {
	std::vector<int> ids;

	if (tickets.empty()) {
		std::cout << "Поиск невозможен. Список заявок пуст.\n";
		return ids;
	}

	std::string srh_unit;
	std::cout << "Введите значение для поиска: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, srh_unit);

	for (const auto& ticket : tickets) {
		if (ticket.getPassengerName().find(srh_unit) != std::string::npos) {
			ids.push_back(ticket.getId());
		}
	}

	return ids;
}

// печать заявки по id
void printBy(const std::vector<int>& ids, const std::list<TicketRequest>& tickets) {
	if (ids.empty()) {
		std::cout << "\n" << " *Совпадений не найдено*\n";
		return;
	}

	std::unordered_set<int> id_set(ids.begin(), ids.end());
	for (const auto& ticket : tickets) {
		if (id_set.count(ticket.getId())) {
			ticket.printTicket();
		}
	}
}

// Фунцкия возврата объекта по id
auto getTicketRequestById(std::list<TicketRequest>& tickets, int id) {
	for (auto it = tickets.begin(); it != tickets.end(); ++it) {
		if (it->getId() == id) {
			return it; // Возвращаем итератор
		}
	}
	return tickets.end(); // Если не найден
}

// фунцкия меню работы с заявкой
int menuInRequestWork(int id) {
	int point;
	while (true) {
		std::cout << "\n";
		std::cout << "\n----------------- Заявка #" << id << "-----------------\n"
			<< "\n"
			<< "1 - Изменить статус заявки \t2 - Удалить заявку\n"
			<< "\t\t3 - Выход\n"
			<< "\n"
			<< "_____________________________________________________" << std::endl
			<< "Выберите пункт: ";

		// проверка на валдиность ввода 
		if (std::cin >> point && point >= 1 && point <= 3) {
			return point;
		}
		std::cin.clear(); // Сброс флага ошибки
		std::cin.ignore(10000, '\n'); // Очистка буфера
		std::cout << "Ошибка! Введите число от 1 до 3!\n";
	}
}

// функция работы с заявкой, удаление и смена статуса
void workInRequest(std::list<TicketRequest>& tickets) { // Принимаем список по ссылке!
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
	std::cout << "\n" << "Это ваша заявка? (y/n)";
	std::cin >> term;

	if (term == "y") {
		int point;
		do {
			point = menuInRequestWork(id);
			switch (point) {
			case 1: {
				std::string new_status;
				std::cout << "Введите новый статус: ";
				std::cin.ignore(); // Очистка буфера
				std::getline(std::cin, new_status);

				// Модифицируем исходный объект через итератор
				it->setStatus(new_status);
				std::cout << "Статус заявки #" << id << " изменен. Текущий статус: " << it->getStatus() << "\n";
				break;
			}
			case 2: {
				// Удаляем заявку из списка через итератор
				std::string corr;
				std::cout << "Вы уверены, что хотите удалить заявку?(y/n)";
				std::cin >> corr;
				if (corr == "y")
				{
					tickets.erase(it);
					std::cout << "\n" << "*Заявка удалена!*\n";
					return; // Выходим из цикла, так как итератор невалиден после удаления
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