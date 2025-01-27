#include "../inc/PmergeMe.hpp"

/*
    Methode de tri Ford Johnson

    - Creer des paires avec les elements
    - Trier les paire
    - Creer une sequence triee des premiers elements (tri par insertion)
    - Inserer les seconds elements
*/

void    sort_vec(std::vector<int>& vec)
{
    bool    is_even_length = vec.size() % 2 == 0;

    // Sort pairs [9, 4, 7, 2, 0, 8] => [4, 9], [2, 7], [0, 8]
}

int main(int argc, char* argv[])
{
    std::vector<int>    container1;
    std::deque<int>     container2;

    try
    {
        container1 = parse_args_vec(argc, argv);
        container2 = parse_args_deq(argc, argv);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Before: ";
    print_vec(container1);

    return 0;
}