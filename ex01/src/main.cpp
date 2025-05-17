#include <iostream>
#include <stack>
#include <cstdlib>
#include <climits>

void print_stack(std::stack<long long> c)
{
    while (!c.empty()) {
        std::cout << c.top() << " ";
        c.pop();
    }
    std::cout << std::endl;
}

int main(int argc, char **argv) {
    if (argc != 2)
        return (std::cerr << "Error" << std::endl, EXIT_FAILURE);

    std::string input = argv[1];

    std::stack<long long> stack;

    size_t i = 0;
    while (i < input.size()) 
    {
        if (std::isdigit(input[i])) 
        {
            long long nb = input[i] - '0';
            if (nb >= 0 && nb <= 9)
                stack.push(nb);
            else
                return (std::cerr << "Error" << std::endl, EXIT_FAILURE);
        } 
        else if (input[i] != ' ') 
        {
            if (stack.size() < 2)
                return (std::cerr << "Error" << std::endl, EXIT_FAILURE);

            long long nb1 = stack.top();
            stack.pop();
            long long nb2 = stack.top();
            stack.pop();

            switch (input[i]) 
            {
                case '+':
                    if (nb2 + nb1 > INT_MAX)
                        return (std::cerr << "Error" << std::endl, EXIT_FAILURE);
                    stack.push(nb2 + nb1);
                    break;
                case '-':
                    if (nb2 - nb1 < INT_MIN)
                        return (std::cerr << "Error" << std::endl, EXIT_FAILURE);
                    stack.push(nb2 - nb1);
                    break;
                case '*':
                    if (nb2 * nb1 > INT_MAX)
                        return (std::cerr << "Error" << std::endl, EXIT_FAILURE);
                    stack.push(nb2 * nb1);
                    break;
                case '/':
                    if (nb1 == 0)
                        return (std::cerr << "Error" << std::endl, EXIT_FAILURE);
                    stack.push(nb2 / nb1);
                    break;
                default:
                    return (std::cerr << "Error" << std::endl, EXIT_FAILURE);
            }
        }
        i++;
        while (i < input.size() && input[i] == ' ')
            i++;
    }
    if (stack.size() > 1)
        return (std::cerr << "Error" << std::endl, EXIT_FAILURE);
    print_stack(stack);
    return (EXIT_SUCCESS);
}