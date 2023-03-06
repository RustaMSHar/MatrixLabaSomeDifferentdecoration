#include "Line.h"

Line::Line(const int lineSize, const int lineSpeed)
{
	timeToStep = milliseconds(1000 / lineSpeed);
	std::uniform_int_distribution<> newRandom{ 0, get_console_width() };
	this->lineSize = lineSize;
	int randCoordX = newRandom(Manager::mersenne);
	std::uniform_int_distribution<> randomizeSymbol{ 33, 127 };
	if (Manager::get_epilepsy_mode())
	{
		std::uniform_int_distribution<> colorDistribution{ 1, 14 };
		textColor = colorDistribution(Manager::mersenne);
	}

	for (int i = get_console_height(); get_console_height() - i < lineSize; i--)
	{
		Symbol* randSymbol = new Symbol(randCoordX, i, 15, randomizeSymbol(Manager::mersenne));
		symbolicLine.push_back(randSymbol);
	}
	set_rand_time_to_start(steady_clock::now());
}


void Line::step_forward()
{
	
	std::uniform_int_distribution<> newRandSymbol{ 33, 127 };
	if (renderingCounter < lineSize)
	{
		symbolicLine[renderingCounter]->print_symbol();
		if (renderingCounter > 0 && symbolicLine.size() > 1)
		{
			symbolicLine[renderingCounter - 1]->set_color(textColor);
			symbolicLine[renderingCounter - 1]->print_symbol();
		}
	}
	else if (symbolicLine.back()->get_coord_y() == 0)
	{
		if (symbolicLine.size() == lineSize)
		{
			symbolicLine.back()->set_color(textColor);
			symbolicLine.back()->print_symbol();
		}
		symbolicLine.front()->clear_symbol();
		delete symbolicLine.front();
		symbolicLine.pop_front();
		deathFlag = symbolicLine.size() == 0;
	}
	else
	{
		symbolicLine.back()->set_color(symbolicLine.front()->get_text_color());
		symbolicLine.back()->print_symbol();
		symbolicLine.push_back(new Symbol(symbolicLine.back()->get_coord_x(), symbolicLine.back()->get_coord_y() - 1,
			15, newRandSymbol(Manager::mersenne)));
		symbolicLine.back()->print_symbol();
		symbolicLine.front()->clear_symbol();
		delete symbolicLine.front();
		symbolicLine.pop_front();
	}
	renderingCounter++;
}

int Line::get_console_width()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo; // Извлекает сведения об указанном буфере экрана консоли
	GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

	// current window size
	short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left;
	return winWidth;
}

int Line::get_console_height()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
	GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

	short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top;
	return winHeight;
}

bool Line::get_death_flag()
{
	return deathFlag;
}

void Line::set_rand_color()
{
	std::uniform_int_distribution<> colorDistribution{ 1, 15 };
	int newColor = colorDistribution(Manager::mersenne);
	for (int i = 0; i < symbolicLine.size(); i++)
	{
		symbolicLine[i]->set_color(newColor);
	}
}

void Line::set_rand_time_to_start(steady_clock::time_point timeNow)
{
	std::uniform_int_distribution<> randTimeDistribution{ 1, 999 };
	timeToStart = timeNow + milliseconds(randTimeDistribution(Manager::mersenne));
}

void Line::try_move(std::chrono::steady_clock::time_point timeNow)
{
	if (timeNow >= timeToStart)
	{
		step_forward();
		timeToStart += timeToStep;
	}
}