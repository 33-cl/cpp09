#include <iostream>
#include <stack>
#include <cstdlib>

void print_stack(std::stack<int> c)
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

    std::stack<int> stack;

    size_t i = 0;
    while (i < input.size()) 
    {
        if (std::isdigit(input[i]) || (input[i] == '-' && i + 1 < input.size() && std::isdigit(input[i + 1]))) 
        {
            int sign = 1;
            if (input[i] == '-') {
                sign = -1;
                i++;
            }
            int nb = sign * (input[i] - '0');
            stack.push(nb);
        } 
        else if (input[i] != ' ') 
        {
            if (stack.size() < 2)
                return (std::cerr << "Error" << std::endl, EXIT_FAILURE);

            int nb1 = stack.top();
            stack.pop();
            int nb2 = stack.top();
            stack.pop();

            switch (input[i]) 
            {
                case '+':
                    stack.push(nb2 + nb1);
                    break;
                case '-':
                    stack.push(nb2 - nb1);
                    break;
                case '*':
                    stack.push(nb2 * nb1);
                    break;
                case '/':
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