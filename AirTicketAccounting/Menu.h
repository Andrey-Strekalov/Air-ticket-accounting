/////////////////////////////////////////////
/////////////     Menu.h     ////////////////
/////////////////////////////////////////////


#pragma once
class Menu

	// ����� ���� ���������

{
public:
	static int mainMenu(); // ������� ����� ���������
	static int ticketMenu(); // ���� �������� � ��������
	static int flightMenu(); // ���� �������� � �������
	static int menuInSearchBlock(); // ���� ������ ������
	static int menuInRequestWork(int id); // ���� ������ � �������
	
};

