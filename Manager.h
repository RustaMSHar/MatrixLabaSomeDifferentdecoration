#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <random>
#include <chrono>
#include <list>
#include <vector>

#include "Line.h"

using namespace std::chrono;

class Line;

class Manager
{
private:
    int numberOfSymbols = 10; // ���-�� ��������
    int lineGenerationFrequency = 1;  //����� ���������
    int lineSpeed = 1; //�������� �����
    static int epilepsyMode; //��� ��������� 
    std::list <Line*> lineList; 

    bool number_validator(const std::string numStr, const int minNum, const int maxNum); //��������� ����� �� ��� �� ���� � �� ���� ��������
public:

    static std::mt19937 mersenne; //��������� ��������������� �����,

    static int get_epilepsy_mode();
    void set_window_size();
    void ask_number_of_symbols();
    void ask_line_generation_frequency();
    void ask_line_speed();
    void ask_epilepsy_mode();
    void run();
    void add_line();
    void delete_line();
    
    bool is_next_second(steady_clock::time_point startTime);
    //steady_clock::time_point get_rand_mstime(steady_clock::time_point startTime, int durationTimeMs);
};