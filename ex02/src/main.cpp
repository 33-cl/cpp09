#include "../inc/PmergeMe.hpp"

/*
    Methode de tri Ford Johnson

    - Creer des paires avec les elements
    - Trier les paire
    - Creer une sequence triee des premiers elements (tri par insertion)
    - Inserer les seconds elements
*/

std::vector<size_t> generate_jacobsthal_sequence(size_t max_size)
{
    std::vector<size_t> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    while (jacobsthal.back() < max_size)
        jacobsthal.push_back(jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2]);
    return jacobsthal;
}

void sort_vec(std::vector<int>& vec)
{
    size_t n = vec.size();
    if (n <= 1)
        return;

    bool is_odd_length = (n % 2 != 0);
    std::vector<int> main_chain, b_elements;

    // Étape 1 : Comparer les paires et stocker les plus grands éléments pour tri
    for (size_t i = 0; i + 1 < n; i += 2)
    {
        if (vec[i] > vec[i + 1])
            std::swap(vec[i], vec[i + 1]);

        main_chain.push_back(vec[i + 1]); // Stocker les plus grands pour tri
        b_elements.push_back(vec[i]);     // Stocker les plus petits
    }

    // Ajouter l'élément impair s'il existe
    if (is_odd_length)
        main_chain.push_back(vec.back());

    // Étape 2 : Trier récursivement les plus grands éléments (main_chain)
    sort_vec(main_chain);

    // Étape 3 : Insérer les petits éléments dans la main_chain en suivant Jacobsthal
    std::vector<int> sorted_vec = main_chain;
    std::vector<size_t> jacobsthal_seq = generate_jacobsthal_sequence(b_elements.size());

    for (size_t i = 0; i < b_elements.size(); ++i)
    {
        int b = b_elements[i];
        size_t idx = std::min(jacobsthal_seq[i], sorted_vec.size());
        std::vector<int>::iterator pos = std::lower_bound(sorted_vec.begin(), sorted_vec.begin() + idx, b);
        sorted_vec.insert(pos, b);
    }

    vec = sorted_vec;
}

// void sort_vec(std::vector<int>& vec)
// {
//     if (vec.size() == 1)
//         return;

//     bool is_odd_length = vec.size() % 2 != 0;
//     std::vector<int> tmp;

//     for (std::vector<int>::iterator it = vec.begin(); it != vec.end() - is_odd_length; it += 2)
//     {
//         // Sort pairs [9, 4, 7, 2, 0, 8, 2] => [4, 9], [2, 7], [0, 8], [2]
//         if (*it > *(it + 1))
//             std::swap(*it, *(it + 1));

//         // Insert first elems of pair
//         std::vector<int>::iterator pos = tmp.begin();
//         while (pos != tmp.end() && *pos < *it)
//             ++pos;
//         tmp.insert(pos, *it);
//     }

//     // Insert second elems of pair
//     for (std::vector<int>::iterator it = vec.begin() + 1; it < vec.end(); it += 2)
//     {
//         std::vector<int>::iterator pos = tmp.begin();
//         while (pos != tmp.end() && *pos < *it)
//             ++pos;
//         tmp.insert(pos, *it);
//     }
    
//     // Add the last alone event if he exists
//     if (is_odd_length)
//     {
//         std::vector<int>::iterator pos = tmp.begin();
//         std::vector<int>::iterator last = vec.end() - 1;
//         while (pos != tmp.end() && *pos < *last)
//             ++pos;
//         tmp.insert(pos, *last);
//     }

//     vec = tmp;
// }


void sort_deq(std::deque<int>& deq)
{
    if (deq.size() == 1)
        return;

    bool is_odd_length = deq.size() % 2 != 0;
    std::deque<int> tmp;

    for (std::deque<int>::iterator it = deq.begin(); it != deq.end() - is_odd_length; it += 2)
    {
        // Sort pairs [9, 4, 7, 2, 0, 8, 2] => [4, 9], [2, 7], [0, 8], [2]
        if (*it > *(it + 1))
            std::swap(*it, *(it + 1));

        // Insert first elems of pair
        std::deque<int>::iterator pos = tmp.begin();
        while (pos != tmp.end() && *pos < *it)
            ++pos;
        tmp.insert(pos, *it);
    }

    // Insert second elems of pair
    for (std::deque<int>::iterator it = deq.begin() + 1; it < deq.end(); it += 2)
    {
        std::deque<int>::iterator pos = tmp.begin();
        while (pos != tmp.end() && *pos < *it)
            ++pos;
        tmp.insert(pos, *it);
    }
    
    // Add the last alone event if he exists
    if (is_odd_length)
    {
        std::deque<int>::iterator pos = tmp.begin();
        std::deque<int>::iterator last = deq.end() - 1;
        while (pos != tmp.end() && *pos < *last)
            ++pos;
        tmp.insert(pos, *last);
    }

    deq = tmp;
}

void verifierVecteurTrie(const std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        if (vec[i] > vec[i + 1]) {
            std::cout << vec[i] << " n'est pas inférieur à " << vec[i + 1] << std::endl;
        }
    }
}

void verifierDequeTrie(const std::deque<int>& dq) {
    for (size_t i = 0; i < dq.size() - 1; ++i) {
        if (dq[i] > dq[i + 1]) {
            std::cout << dq[i] << " n'est pas inférieur à " << dq[i + 1] << std::endl;
        }
    }
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

        // std::cout << "Before: ";
        // print_vec(container1);

        start_vec = clock();
        sort_vec(container1);
        end_vec = clock();

        //verifierVecteurTrie(container1);

        start_deq = clock();
        sort_deq(container2);
        end_deq = clock();
        verifierDequeTrie(container2);

        // std::cout << "After: ";
        // print_vec(container1);


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