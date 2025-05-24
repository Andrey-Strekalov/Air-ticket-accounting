/////////////////////////////////////////////
/////////////     Print.h    ////////////////
/////////////////////////////////////////////


#pragma once
#include <list>
#include <vector>
#include "Board.h"
#include "TicketRequest.h"

class Print
{
public:
	Print();
	~Print();

	// фунцкии полной и сокращенной информации по заявкам с перегрузкой по параметрам
	static void printAllTickets(const std::list<TicketRequest>& tickets);
	static void printAllTickets(const std::list<TicketRequest>& tickets, bool shortprint);

	// Вывод информации о рейсах
	static void printFlightInfo(const std::list<Board>& flights);
	static void printAllFlights(const std::list<Board>& flights);

	// Вывод списка заявок по списку id
	static void printBy(const std::vector<int>& ids, const std::list<TicketRequest>& tickets);

private:

};

