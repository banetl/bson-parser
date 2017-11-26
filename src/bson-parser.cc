#include <fstream>
#include <iostream>
#include <vector>

#include "document.hh"
#include "parser.hh"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./bson-parser file.bson" << std::endl;
        return 1;
    }

    try
    {
        // open file in binary mode && set the input position indicator to the end
        std::ifstream file(argv[1], std::ios::binary | std::ios::ate);
        if (!file.is_open())
            throw std::invalid_argument("Cannot open input file.");
        // Get the size and set the position indicator to the start again
        auto size = file.tellg();
        file.seekg(0);

        std::vector<unsigned char> buffer(size);
        // Implicitely calls the () operator ==> equivalent to !fail()
        // this way of reading the buffer is inspired by the example here:
        // http://en.cppreference.com/w/cpp/io/basic_ifstream
        if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
            throw std::invalid_argument("Cannot read input file.");
        file.close();

        bson::Parser parser(buffer);
        auto document = parser.parse();
        document->dump(std::cout);

    } catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 2;
    }

    return 0;
}
