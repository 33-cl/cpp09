#include "../inc/bitcoin.hpp"

float    find_before(std::map<std::string, float> data, std::string date)
{
    MapIterator it;

    for (it = data.begin(); it != data.end(); ++it)
    {
        if (date < it->first)
        {
            it--;
            return it->second;
        }
    }
    it--;
    return it->second;
}

bool is_all_num(const std::string& value)
{
    int nb_neg = 0;
    int nb_dot = 0;

    for (size_t i = 0; i < value.size(); ++i) 
    {
        if (value[i] == '-')
            nb_neg++;
        else if (value[i] == '.')
            nb_dot++;
        if ((!isdigit(value[i]) && value[i] != '-' && value[i] != '.') || nb_dot > 1 || nb_neg > 1) 
        {
            return false;
        }
    }
    return true;
}
