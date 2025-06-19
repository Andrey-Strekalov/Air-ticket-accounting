/////////////////////////////////////////////
/////////////     Print.h    ////////////////
/////////////////////////////////////////////


#pragma once
#include <list>
#include <vector>
#include "Board.h"
#include "TicketRequest.h"

// класс печати информации, экземпляр не создается, все методы статические 

class Print
{
public:
	Print();
	~Print();

	// фунцкии полной и сокращенной информации по заявкам с перегрузкой по параметрам
	static void printAllTickets(const std::list<TicketRequest>& tickets); // печать списка заявок с полной информацией
	static void printAllTickets(const std::list<TicketRequest>& tickets, bool shortprint); // печать списка заявок с краткой информацией

	// Вывод информации о рейсах
	static void printFlightInfo(const std::list<Board>& flights); // печать информации определенного рейса
	static void printAllFlights(const std::list<Board>& flights); // печать списка всех рейсов 

	// Вывод списка заявок по списку id
	static void printBy(const std::vector<int>& ids, const std::list<TicketRequest>& tickets);

private:

};

