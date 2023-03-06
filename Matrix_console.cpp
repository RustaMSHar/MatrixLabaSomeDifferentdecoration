// Matrix_console.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Manager.h"
#include "Symbol.h"
#include "Line.h"

int main()
{
    setlocale(LC_ALL, "ru");
    Manager newManager;
    
    newManager.ask_number_of_symbols();
    newManager.ask_line_generation_frequency();
    newManager.ask_line_speed();
    newManager.ask_epilepsy_mode();
    newManager.set_window_size();
    newManager.run();

   

}

