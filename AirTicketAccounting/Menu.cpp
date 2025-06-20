﻿/////////////////////////////////////////////
////////////      Menu.cpp     //////////////
/////////////////////////////////////////////


#include <limits>
#include <iostream>

#include "Menu.h"

// функция главного меню программы
int Menu::mainMenu() { 
	int point;
	while (true) {
		std::cout << "\n"
			<< "\n---------------- Главное меню ---------------\n"
			<< "\n"
			<< " 1 - Работа с заявками \t2 - Работа с рейсами\n"
			<< " 3 - Выход из программы \n"
			<< "\n"
			<< "_____________________________________________" << std::endl
			<< "Выберите пункт: ";

		if (std::cin >> point && point >= 1 && point <= 3) return point;

		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Ошибка ввода! Введите число от 1 до 3!\n";
	}
}


// меню операций с заявками
int Menu::ticketMenu() { 
	int point;
	while (true) {
		std::cout << "\n"
			<< "\n---------------- Меню заявок ----------------\n"
			<< "\n"
			<< " 1 - Заполнить заявку \t2 - Посмотреть заявки\n"
			<< " 3 - Поиск заявок\t4 - Работа с заявкой         \n"
			<< " 5 - Выход в главное меню\n"
			<< "\n"
			<< "_____________________________________________" << std::endl
			<< "Выберите пункт: ";

		// проверка на валидность ввода 
		if (std::cin >> point && point >= 1 && point <= 5) {
			return point;
		}
		std::cin.clear(); // Сброс флага ошибки
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Ошибка! Введите число от 1 до 5!\n";
	}
}

// меню операций с рейсами
int Menu::flightMenu() {
	int point;
	while (true) {
		std::cout << "\n"
			<< "\n-------------------- Меню рейсов -------------------\n"
			<< "\n"
			<< " 1 - Зарегистрировать рейс  \t2 - Посмотреть рейсы\n"
			<< " 3 - Просмотреть информацию о рейсе \t4 - Выход в главное меню\n"
			<< "\n"
			<< "____________________________________________________" << std::endl
			<< "Выберите пункт: ";

		if (std::cin >> point && point >= 1 && point <= 4) return point;

		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Ошибка ввода! Введите число от 1 до 4!\n";
	}
}


// фунцкия меню работы с заявкой
int Menu::menuInRequestWork(int id) {
	int point;
	while (true) {
		std::cout << "\n";
		std::cout << "\n----------------- Заявка #" << id << " ----------------\n"
			<< "\n"
			<< " 1 - Изменить статус заявки \t2 - Удалить заявку\n"
			<< " 3 - Выход\n"
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

// меню поиска заявок
int Menu::menuInSearchBlock() {
	int point;
	while (true) {
		std::cout << "\n"
			<< "\n---------------- Меню поиска ----------------\n"
			<< "\n"
			<< " 1 - По имени \t2 - По номеру рейса\n"
			<< " 3 - По ID \t4 - По пункту назначения\n"
			<< " 5 - По дате вылета \t6 - Выход\n"
			<< "\n"
			<< "_____________________________________________" << std::endl
			<< "Выберите пункт: ";

		if (std::cin >> point && point >= 1 && point <= 6) {
			return point;
		}
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Ошибка! Введите число от 1 до 6!\n";
	}
}