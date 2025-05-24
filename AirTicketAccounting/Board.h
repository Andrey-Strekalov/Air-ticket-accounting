/////////////////////////////////////////////
////////////      Board.h    ////////////////
/////////////////////////////////////////////

#pragma once

#include <list>
#include <string>
#include "FlightInfo.h"

class TicketRequest;



class Board : public FlightInfo {
public:
	Board();
	~Board();

	// Сеттеры
	
	void setCapacity(int value);
	void setAvailableSeats(int value);
	void setAircraftNumber(const std::string& value);

	// Геттеры
	int getCapacity() const;
	int getAvailableSeats() const;
	std::string getAircraftNumber() const;
	const std::list<TicketRequest>& getPassengers() const;

	// Методы
	void printInfo() const;
	void calculateAvailableSeats();
	void printPassengersList() const;
	void addPassenger(const TicketRequest& ticket);

	static std::list<Board> loadFromFile(const std::string& filename); // чтение объекта из файла
	static void saveToFile(const std::list<Board>& flights, const std::string& filename); // сохранение объекта в файл
	static void assignPassengers(std::list<Board>& flights, std::list<TicketRequest>& tickets);
	//static void changeFlightDate(std::list<Board>& flights);


	// регистрация авиасудна на рейс
	static void flightChekIn(Board* flights);

private:
	int capacity;
	int availableSeats;
	std::string aircraftNumber;
	std::list<TicketRequest> passengers;
};