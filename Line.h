#pragma once

#include <Windows.h>
#include <vector>
#include <iostream>
#include <deque>
#include <random>
#include <chrono>

#include "Symbol.h"
#include "Manager.h"

using namespace std::chrono;

class Symbol;

class Line
{
private:
	bool deathFlag = false;
	int lineSize;
	int renderingCounter = 0;
	int textColor = 2;
	steady_clock::duration timeToStep;
	steady_clock::time_point timeToStart;
	std::deque <Symbol*> symbolicLine;
public:

	Line(const int lineSize, const int lineSpeed);
	//void move_line();
	void step_forward();
	int get_console_width();
	int get_console_height();
	bool get_death_flag();
	void set_rand_color();
	void set_rand_time_to_start(steady_clock::time_point timeNow);
	void try_move(std::chrono::steady_clock::time_point timeNow);
};