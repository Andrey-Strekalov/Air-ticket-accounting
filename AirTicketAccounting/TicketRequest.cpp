#include <iostream>
#include <string>
#include<list>
#include "TicketRequest.h"

TicketRequest::TicketRequest()
{
}

TicketRequest::~TicketRequest()
{
}

// Сеттеры класса
void TicketRequest::setId(int value) { id = value; }
void TicketRequest::setPassengerName(std::string name) { passengerName = name; }
void TicketRequest::setFlightNumber(std::string fl_num) { flightNumber = fl_num; };
void TicketRequest::setDepartureDate(std::string date) { departurDate = date; }
void TicketRequest::setDestination(std::string value) { destination = value; }
void TicketRequest::setStatus(std::string value) { status = value; }

// Геттеры класса
int TicketRequest::getId() const { return id; }
std::string TicketRequest::getPassengerName() const { return passengerName; }
std::string TicketRequest::getFlightNumber() { return flightNumber; }
std::string TicketRequest::getDepartureDate() { return departurDate; }
std::string TicketRequest::getDestination() { return  destination; }
std::string TicketRequest::getStatus() { return  status; }

// Остальные методы

void TicketRequest::printTicket() const{ // печать объекта
		std::cout << "\n" << std::endl;
		std::cout << "Заявка №" << id << std::endl;
		std::cout << "Рейс №" << flightNumber << std::endl;
		std::cout << "Пассажир: " << passengerName << std::endl;
		std::cout << "Дата вылета: " << departurDate << std::endl;
		std::cout << "Пункт назначения: " << destination << std::endl;
		std::cout << "Статус заявки: " << status << std::endl;
}