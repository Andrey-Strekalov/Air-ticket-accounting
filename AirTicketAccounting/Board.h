/////////////////////////////////////////////
////////////      Board.h    ////////////////
/////////////////////////////////////////////

#pragma once

#include <list>
#include <string>
#include "FlightInfo.h"

class TicketRequest;

// класс воздушного судна

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
	void printInfo() const override; // вывод информации о рейсе
	void printPassengersList() const; // вывод списка пассажиров
	void calculateAvailableSeats(); // вычисление количества свободных мест
	void addPassenger(const TicketRequest& ticket); // добавление пассажира в список

	static std::list<Board> loadFromFile(const std::string& filename); // чтение объекта из файла
	static void saveToFile(const std::list<Board>& flights, const std::string& filename); // сохранение объекта в файл
	// составление списка пассажиров (работает в паре с методом addPassenger())
	static void assignPassengers(std::list<Board>& flights, std::list<TicketRequest>& tickets); 
	static void flightChekIn(Board* flights); // регистрация авиасудна на рейс

private:
	int capacity = 0; // вместимость
	int availableSeats = 0; // свободные места
	std::string aircraftNumber; // регистрационный номер воздушного судна
	std::list<TicketRequest> passengers; // список пассажиров
};