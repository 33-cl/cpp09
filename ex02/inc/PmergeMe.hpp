#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <deque>

void    print_vec(std::vector<int> vec);
void    print_deq(std::deque<int> vec);

std::vector<int> parse_args_vec(int argc, char** argv);
std::deque<int> parse_args_deq(int argc, char** argv);