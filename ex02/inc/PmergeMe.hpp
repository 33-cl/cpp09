#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <deque>
#include <ctime>
#include <algorithm>

template <typename Container>
void print_container(const Container& container);

template <typename Container>
Container parse_args(int argc, char** argv);

template <typename T>
void swap(T& val1, T& val2)
{
    T   temp;

    temp = val1;
    val1 = val2;
    val2 = temp;
}