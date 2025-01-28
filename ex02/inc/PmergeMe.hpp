#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <deque>
#include <ctime>

void    print_vec(std::vector<int> vec);
void    print_deq(std::deque<int> vec);

std::vector<int> parse_args_vec(int argc, char** argv);
std::deque<int> parse_args_deq(int argc, char** argv);

template <typename T>
void    swap(T& val1, T& val2)
{
    T   temp;

    temp = val1;
    val1 = val2;
    val2 = temp;
}