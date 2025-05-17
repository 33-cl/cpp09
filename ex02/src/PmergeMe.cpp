#include "../inc/PmergeMe.hpp"

template <typename Container>
void print_container(const Container& container)
{
    for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it) {
       std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename Container>
Container parse_args(int argc, char** argv)
{
    Container numbers;

    for (int i = 1; i < argc; ++i) {

        std::string arg = argv[i];
        long long num = 0;
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
            
            if (num > INT_MAX / 10)
                throw std::overflow_error("Integer overflow");
            
            num = num * 10;
            
            if (num > INT_MAX - (arg[j] - '0'))
                throw std::overflow_error("Integer overflow");
                
            num = num + (arg[j] - '0');
        }

        if (negative) {
            if (-num < INT_MIN)
                throw std::overflow_error("Integer overflow");
            numbers.push_back(static_cast<int>(-num));
        } else {
            if (num > INT_MAX)
                throw std::overflow_error("Integer overflow");
            numbers.push_back(static_cast<int>(num));
        }
    }

    return numbers;
}

// Explicit template instantiations
template void print_container<std::vector<int> >(const std::vector<int>&);
template void print_container<std::deque<int> >(const std::deque<int>&);
template std::vector<int> parse_args<std::vector<int> >(int, char**);
template std::deque<int> parse_args<std::deque<int> >(int, char**);