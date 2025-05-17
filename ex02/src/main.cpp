#include "../inc/PmergeMe.hpp"

template <typename Container>
Container generate_jacobsthal_sequence(int max_size)
{
    Container jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    while (jacobsthal.back() < max_size)
        jacobsthal.push_back(jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2]);
    return jacobsthal;
}

template <typename Container>
void check_container_sorted(const Container& container) {
    for (size_t i = 0; i < container.size() - 1; ++i) {
        if (container[i] > container[i + 1]) {
            std::cout << container[i] << " shouldn't be superior to " << container[i + 1] << std::endl;
        }
    }
}

template <typename Container>
void sort_container(Container& container)
{
    if (container.size() <= 1)
        return;

    Container mainChain;
    Container pending;

    // Pair and split elements
    for (size_t i = 0; i < container.size(); i += 2)
    {
        if (i + 1 < container.size())
        {
            if (container[i] > container[i + 1]) {
                typename Container::value_type temp = container[i];
                container[i] = container[i + 1];
                container[i + 1] = temp;
            }
            mainChain.push_back(container[i]);
            pending.push_back(container[i + 1]);
        }
        else
            mainChain.push_back(container[i]);
    }

    // Recursively sort main chain
    sort_container(mainChain);

    // Generate Jacobsthal sequence
    Container jacobsthal = generate_jacobsthal_sequence<Container>(pending.size());
    std::vector<bool> inserted(pending.size(), false);

    // Insert elements using Jacobsthal sequence
    for (int i = static_cast<int>(jacobsthal.size()) - 1; i >= 0; --i)
    {
        size_t jacob_index = static_cast<size_t>(jacobsthal[i] - 1);
        if (jacob_index < pending.size() && !inserted[jacob_index])
        {
            typename Container::value_type toInsert = pending[jacob_index];
            typename Container::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), toInsert);
            mainChain.insert(it, toInsert);
            inserted[jacob_index] = true;
        }
    }

    // Insert any remaining elements
    for (size_t i = 0; i < pending.size(); ++i)
    {
        if (!inserted[i])
        {
            typename Container::value_type toInsert = pending[i];
            typename Container::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), toInsert);
            mainChain.insert(it, toInsert);
        }
    }

    // Copy back to original container
    container.assign(mainChain.begin(), mainChain.end());
}

int main(int argc, char* argv[])
{
    if (argc <= 1) 
        return (std::cerr << "Error: No arguments provided\n", EXIT_FAILURE);

    if (argv[1][0] == '\0')
        return (std::cerr << "Error: Empty argument provided\n", EXIT_FAILURE);

    std::vector<int>    container1;
    std::deque<int>     container2;

    try
    {
        clock_t start_vec, end_vec;
        clock_t start_deq, end_deq;

        container1 = parse_args<std::vector<int> >(argc, argv);
        container2 = parse_args<std::deque<int> >(argc, argv);

        if (container1.size() == 0)
            return (std::cerr << "Error: No arguments provided\n", EXIT_FAILURE);

        std::cout << "Before: ";
        print_container(container1);

        start_vec = clock();
        sort_container(container1);
        end_vec = clock();
        check_container_sorted(container1);

        start_deq = clock();
        sort_container(container2);
        end_deq = clock();
        check_container_sorted(container2);

        std::cout << "After: ";
        print_container(container1);

        double duration_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC;
        std::cout << "Time to process a range of " << container1.size() << " elements with std::vector : " << duration_vec * 1000000 << " us" << std::endl;

        double duration_deq = static_cast<double>(end_deq - start_deq) / CLOCKS_PER_SEC;
        std::cout << "Time to process a range of " << container1.size() << " elements with std::deque  : " << duration_deq * 1000000 << " us" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}