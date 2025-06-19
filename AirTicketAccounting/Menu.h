/////////////////////////////////////////////
/////////////     Menu.h     ////////////////
/////////////////////////////////////////////


#pragma once
class Menu

	// класс меню программы

{
public:
	static int mainMenu(); // главное мменю программы
	static int ticketMenu(); // меню операций с заявками
	static int flightMenu(); // меню операций с рейсами
	static int menuInSearchBlock(); // меню поиска заявок
	static int menuInRequestWork(int id); // меню работы с заявкой
	
};

