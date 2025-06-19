/////////////////////////////////////////////
////////////      TicketRequest.h    ////////
/////////////////////////////////////////////

#pragma once
#include<list>
#include <string>

#include "FlightInfo.h"

class Board;

// класс заявки на билет

class TicketRequest : public FlightInfo
{
public:
	TicketRequest();
	~TicketRequest();

	// Сеттеры класса
	void setId(int id);
	void setStatus(std::string status);
	void setPassengerName(std::string name);


	// Геттеры класса
	int getId() const;
	std::string getStatus()const;
	std::string getPassengerName() const;

	// Остальные методы
	void printInfo() const override; // печать объекта
	static std::list<TicketRequest> loadFromFile(const std::string& filename); // чтение объекта из файла
	static void saveToFile(const std::list<TicketRequest>& tickets, const std::string& filename); // сохранение объекта в файл

	// функция работы с заявкой, удаление и изменение статуса
	static void workInRequest(std::list<TicketRequest>& tickets);

	// сортировка контейнера заявок по алфавиту
	static void sortList(std::list<TicketRequest>& container);

	// функция получения объекта заявки по id 
	static std::list<TicketRequest>::iterator
		getTicketRequestById(std::list<TicketRequest>& tickets, int id);

	// функция создания объекта заявки на билет
	static void createTicketRequest(TicketRequest* ticket, std::list<Board>& flights); // создание заявки



private:
	int id; // индевидуальный номер заявки
	std::string status; // статус заявки
	std::string passengerName; // ФИО пассажира

};

