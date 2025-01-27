#pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

typedef std::map<std::string, float>::iterator MapIterator;

std::map<std::string, float>    extract_data();
bool                            is_all_num(const std::string& value);
void                            parse_line(const std::string& line);
float                           find_before(std::map<std::string, float> data, std::string date);
bool                            compareDates(const std::string& date1, const std::string& date2);