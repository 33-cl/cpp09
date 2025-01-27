#include "../inc/PmergeMe.hpp"

void    print_vec(std::vector<int> vec)
{
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
       std::cout << *it << " ";
   }
   std::cout << std::endl;
}

void    print_deq(std::deque<int> deq)
{
    for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it) {
       std::cout << *it << " ";
   }
   std::cout << std::endl;
}



std::vector<int> parse_args_vec(int argc, char** argv)
{
    std::vector<int> numbers;

    for (int i = 1; i < argc; ++i) {

        std::string arg = argv[i];
        int num = 0;
        bool negative = false;
        size_t j = 0;

        if (arg[j] == '-') {
            negative = true;
            ++j;
        }

        for (; j < arg.length(); ++j)
        {
            if (!std::isdigit(arg[j]))
                throw std::invalid_argument("Invalid argument");
            num = num * 10 + (arg[j] - '0');
        }

        if (j == arg.length())
        {
            numbers.push_back(negative ? -num : num);
        }
    }

    return numbers;
}

std::deque<int> parse_args_deq(int argc, char** argv)
{
    std::deque<int> numbers;

    for (int i = 1; i < argc; ++i) {

        std::string arg = argv[i];
        int num = 0;
        bool negative = false;
        size_t j = 0;

        if (arg[j] == '-') {
            negative = true;
            ++j;
        }

        for (; j < arg.length(); ++j)
        {
            if (!std::isdigit(arg[j]))
                throw std::invalid_argument("Invalid argument");
            num = num * 10 + (arg[j] - '0');
        }

        if (j == arg.length())
        {
            numbers.push_back(negative ? -num : num);
        }
    }

    return numbers;
}