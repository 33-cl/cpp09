#include "../inc/bitcoin.hpp"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    std::map<std::string, float>    data;
    std::ifstream                   file(argv[1]);
    if (!file)
        return (std::cout << "Error: could not open file\n", 1);

    try
    {
        data = extract_data();        
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

    std::string line;
    std::getline(file, line); // Skip first line

    while (std::getline(file, line))
    {
        try
        {
            parse_line(line);

            std::string date   = line.substr(0, 10);
            float       value  = atof((line.substr(13, line.size() - 1)).c_str());
            float       result = 0;
  
            MapIterator it = data.find(date);
            if (it != data.end())
                result = it->second * value;
            else
                result = find_before(data, date);
            std::cout << date << " => " << value << " = " << result * value << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << '\n';
        }    
    }
}