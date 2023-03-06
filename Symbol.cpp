#include "Symbol.h"

Symbol::Symbol(int x, int y, int textColor, int symbolType)
{
	this->coord.X = x;
	this->coord.Y = y;
	this->textColor = textColor;
	this->symbolType = symbolType;
}

Symbol::Symbol(const Symbol& other)
{
	std::cout << "copy constructor" << std::endl;
}

void Symbol::print_symbol()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);// �������� ������ �� �������
	SetConsoleTextAttribute(hStdOut, (WORD)(0 << 4 | textColor)); //������������� �������� ��������
	SetConsoleCursorPosition(hStdOut, coord); //��������� ������� � �������
	_putch(symbolType); //������� �� ����� ������
	SetConsoleTextAttribute(hStdOut, (WORD)(0 << 4 | 15)); // ������������� ���� �����
}

void Symbol::clear_symbol()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdOut, coord);
	_putch(32);
}

int Symbol::get_coord_x()
{
	return coord.X;
}

int Symbol::get_coord_y()
{
	return coord.Y;
}

int Symbol::get_text_color()
{
	return textColor;
}

int Symbol::get_symbol_type()
{
	return symbolType;
}

void Symbol::set_color(int newColor)
{
	this->textColor = newColor;
}