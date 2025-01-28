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
    if (vec.size() == 1)
        return;

    bool                is_odd_length = vec.size() % 2 != 0;
    std::vector<int>    tmp;

    for (size_t  i = 0; i < vec.size() - is_odd_length; i += 2)
    {
        // Sort pairs [9, 4, 7, 2, 0, 8, 2] => [4, 9], [2, 7], [0, 8], [2]
        if (vec[i] > vec[i + 1])
            swap(vec[i], vec[i + 1]);

        // Insert first elems of pair
        size_t pos = 0;
        while (pos < tmp.size() && tmp[pos] < vec[i])
            pos++;
        tmp.insert(tmp.begin() + pos, vec[i]);
    }

    // Insert second elems of pair
    for (size_t i = 1; i < vec.size(); i += 2)
    {
        size_t pos = 0;
        while (pos < tmp.size() && tmp[pos] < vec[i])
            pos++;
        tmp.insert(tmp.begin() + pos, vec[i]);
    }
    
    // Add the last alone event if he exists
    if (is_odd_length)
    {
        size_t pos = 0;
        while (pos < tmp.size() && tmp[pos] < vec[vec.size() - 1])
            pos++;
        tmp.insert(tmp.begin() + pos, vec[vec.size() - 1]);
    }

    vec = tmp;
}

void    sort_deq(std::deque<int>& deq)
{
    if (deq.size() == 1)
        return;

    bool                is_odd_length = deq.size() % 2 != 0;
    std::deque<int>    tmp;

    for (size_t  i = 0; i < deq.size() - is_odd_length; i += 2)
    {
        // Sort pairs [9, 4, 7, 2, 0, 8, 2] => [4, 9], [2, 7], [0, 8], [2]
        if (deq[i] > deq[i + 1])
            swap(deq[i], deq[i + 1]);

        // Insert first elems of pair
        size_t pos = 0;
        while (pos < tmp.size() && tmp[pos] < deq[i])
            pos++;
        tmp.insert(tmp.begin() + pos, deq[i]);
    }

    // Insert second elems of pair
    for (size_t i = 1; i < deq.size(); i += 2)
    {
        size_t pos = 0;
        while (pos < tmp.size() && tmp[pos] < deq[i])
            pos++;
        tmp.insert(tmp.begin() + pos, deq[i]);
    }
    
    // Add the last alone event if he exists
    if (is_odd_length)
    {
        size_t pos = 0;
        while (pos < tmp.size() && tmp[pos] < deq[deq.size() - 1])
            pos++;
        tmp.insert(tmp.begin() + pos, deq[deq.size() - 1]);
    }

    deq = tmp;
}

int main(int argc, char* argv[])
{
    std::vector<int>    container1;
    std::deque<int>     container2;

    try
    {
        clock_t start_vec, end_vec;
        clock_t start_deq, end_deq;

        container1 = parse_args_vec(argc, argv);
        container2 = parse_args_deq(argc, argv);

        std::cout << "Before: ";
        print_vec(container1);

        start_vec = clock();
        sort_vec(container1);
        end_vec = clock();

        start_deq = clock();
        sort_deq(container2);
        end_deq = clock();

        std::cout << "After: ";
        print_vec(container1);


        double duration_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC;
        std::cout << "Time to process a range of 5 elements with std::vector : " << duration_vec * 1000 << " ms" << std::endl;

        double duration_deq = static_cast<double>(end_deq - start_deq) / CLOCKS_PER_SEC;
        std::cout << "Time to process a range of 5 elements with std::deque  : " << duration_deq * 1000 << " ms" << std::endl;

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }


    return 0;
}