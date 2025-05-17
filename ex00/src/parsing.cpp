#include "../inc/bitcoin.hpp"

std::map<std::string, float>    extract_data()
{
    std::map<std::string, float>    data;
    std::ifstream file("data.csv");
    if (!file)
        throw std::invalid_argument("cannot find/open data.csv");

    std::string date;
    std::string value;
    std::getline(file, date);
    for (int i = 0; i < 1614; i++)
    {
        std::getline(file, date, ',');
        std::getline(file, value);

        data[date] = atof(value.c_str());
    }
    return data;
}

/*
    Returns a bool indicating if the year is leap    
*/

bool is_leap_year(int year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/*
    Returns a bool indicating is the day is valid depending of the month and the year
*/

bool is_valid_day(int year, int month, int day) {
    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && is_leap_year(year))
        days_in_month[1] = 29;
    return day >= 1 && day <= days_in_month[month - 1];
}

void parse_line(const std::string& line) {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    if (line.size() < 14)
        throw std::length_error("Error: bad input => " + line);

    // Parse year
    int year = std::atoi(line.substr(0, 4).c_str());
    if (year < 2009 || year > now->tm_year + 1900 || line[4] != '-')
        throw std::invalid_argument("Error: bad input => " + line);

    // Parse month
    int month = std::atoi(line.substr(5, 2).c_str());
    if (month < 1 || month > 12 || line[7] != '-')
        throw std::invalid_argument("Error: bad input => " + line);

    // Parse day
    int day = std::atoi(line.substr(8, 2).c_str());
    if ((year == 2009 && month == 01 && day == 01) || !is_valid_day(year, month, day))
        throw std::invalid_argument("Error: invalid date => " + line);

    // Check date is not in the future
    if (year > now->tm_year + 1900 || 
        (year == now->tm_year + 1900 && month > now->tm_mon + 1) || 
        (year == now->tm_year + 1900 && month == now->tm_mon + 1 && day > now->tm_mday)) {
        throw std::invalid_argument("Error: date in the future => " + line);
    }

    // Check between 2 values
    if (line.substr(10, 3) != " | ")
        throw std::invalid_argument("Error: bad input => " + line);

    // Check the value is valid
    std::string strval = line.substr(13);
    if (!is_all_num(strval))
        throw std::invalid_argument("Error: bad value => " + strval);
    float value = std::atof(strval.c_str());
    if (value < 0)
        throw std::invalid_argument("Error: not a positive number");
    if (value > 1000)
        throw std::invalid_argument("Error: too large a number");
}
