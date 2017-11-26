#include <iomanip>


namespace utils
{
    // Get the level of indentation in the stream with std::ios::xalloc()
    inline long int& indent(std::ostream& ostr)
    {
        static const long int indent_index = std::ios::xalloc();
        return ostr.iword(indent_index);
    }
    // std::endl and set as many tabs as the level of indentation
    std::ostream& iendl(std::ostream& ostr);
    // increment indentation and endl
    std::ostream& incendl(std::ostream& ostr);
    // decrement indentation and endl
    std::ostream& decendl(std::ostream& ostr);

}
