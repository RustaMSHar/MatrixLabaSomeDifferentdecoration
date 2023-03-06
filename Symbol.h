#pragma once

#include <conio.h>
#include <Windows.h>
#include <iostream>

#include "Manager.h"

class Symbol
{
private:
	int textColor = 2;
	int symbolType;
	COORD coord; //ќпредел€ет координаты символьной €чейки в буфере экрана консоли
public:
	Symbol(int x, int y, int textColor, int symbolType);
	Symbol(const Symbol& other);
	void print_symbol();
	void clear_symbol();
	int get_coord_x();
	int get_coord_y();
	int get_text_color();
	int get_symbol_type();
	void set_color(int newColor);
};