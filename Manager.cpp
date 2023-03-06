#include "Manager.h"

std::mt19937 Manager::mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
int Manager::epilepsyMode = 0;


void Manager::ask_number_of_symbols()
{
    bool numberDoneFlag = false;
    system("cls");
    while (!numberDoneFlag)
    {
        std::string numberStr;
        std::cout << "Введите длину линии (количество символов от 1 до 30): ";
        getline(std::cin, numberStr);
        if (!number_validator(numberStr, 1, 30))
        {
            std::cout << "Введенные данные не соответствуют условиям! Повторите попытку." << std::endl;
            numberDoneFlag = false;
        }
        else
        {
            numberOfSymbols = std::stoi(numberStr);
            numberDoneFlag = true;
        }
    }
}

void Manager::ask_line_generation_frequency()
{
    bool numberDoneFlag = false;
    system("cls");
    while (!numberDoneFlag)
    {
        std::string numberStr;
        std::cout << "Введите частоту генерации линий (количество линий в секунду от 1 до 30): ";
        getline(std::cin, numberStr);
        if (!number_validator(numberStr, 1, 30))
        {
            std::cout << "Введенные данные не соответствуют условиям! Повторите попытку." << std::endl;
            numberDoneFlag = false;
        }
        else
        {
            lineGenerationFrequency = std::stoi(numberStr);
            numberDoneFlag = true;
        }
    }
}

void Manager::ask_line_speed()
{
    bool numberDoneFlag = false;
    system("cls");
    while (!numberDoneFlag)
    {
        std::string numberStr;
        std::cout << "Введите скорость линии (количество символов в секунду от 1 до 30): ";
        getline(std::cin, numberStr);
        if (!number_validator(numberStr, 1, 30))
        {
            std::cout << "Введенные данные не соответствуют условиям! Повторите попытку." << std::endl;
            numberDoneFlag = false;
        }
        else
        {
            lineSpeed = std::stoi(numberStr);
            numberDoneFlag = true;
        }
    }
}

void Manager::ask_epilepsy_mode()
{
    bool numberDoneFlag = false;
    system("cls");
    while (!numberDoneFlag)
    {
        std::string numberStr;
        std::cout << "Введите мод эпилепсии (1 - ON, 0 - OFF): ";
        getline(std::cin, numberStr);
        if (!number_validator(numberStr, 0, 1))
        {
            std::cout << "Введенные данные не соответствуют условиям! Повторите попытку." << std::endl;
            numberDoneFlag = false;
        }
        else
        {
            epilepsyMode = std::stoi(numberStr);
            numberDoneFlag = true;
        }
    }
}

bool Manager::number_validator(const std::string numStr, const int minNum, const int maxNum) 
{
    if (numStr.length() < 1) return false;
    for (size_t i = 0; i < numStr.length(); i++)
    {
        if (!isdigit(numStr[i]))
        {
            return false;
        }
    }
    if (std::stoi(numStr) > maxNum || std::stoi(numStr) < minNum)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Manager::set_window_size()
{
    system("cls");
    // get handle to the console window
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &info);

    // retrieve screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

    // current window size
    short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
    short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

    // current screen buffer size
    short scrBufferWidth = scrBufferInfo.dwSize.X;
    short scrBufferHeight = scrBufferInfo.dwSize.Y;

    // to remove the scrollbar, make sure the window height matches the screen buffer height
    COORD newSize;
    newSize.X = scrBufferWidth;
    newSize.Y = winHeight;

    // set the new screen buffer dimensions
    int Status = SetConsoleScreenBufferSize(hOut, newSize);
    if (Status == 0)
    {
        std::cout << "SetConsoleScreenBufferSize() failed! Reason : " << GetLastError() << std::endl;
        exit(Status);
    }
}

int Manager::get_epilepsy_mode()
{
    return epilepsyMode;
}

void Manager::add_line()
{
    lineList.push_back(new Line(numberOfSymbols, lineSpeed));
}

void Manager::delete_line()
{
    delete lineList.front();
    lineList.pop_front();
}


bool Manager::is_next_second(steady_clock::time_point startTime)
{
    return steady_clock::now() - startTime >= milliseconds(1000);
}

void Manager::run()
{
    steady_clock::time_point start = steady_clock::time_point(milliseconds(0));
    while (true)
    {
        if (is_next_second(start))
        {
            start = steady_clock::now();
            for (int i = 0; i < lineGenerationFrequency; i++)
            {
                add_line();
            }
        }
        for (Line* line : lineList)
        {
            line->try_move(steady_clock::now());
        }
        lineList.remove_if([](Line* line)
            {
                if (line->get_death_flag())
                {
                    delete line;
                    return true;
                }
                else { return false; }
            }
        );
    }
}