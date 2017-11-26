#include <iostream>

#include "utils.hh"

namespace utils
{

    std::ostream& iendl(std::ostream& ostr)
    {
        ostr << std::endl;
        char fill = ostr.fill(' ');
        return ostr << std::setw(indent(ostr))
            << ""
            << std::setfill(fill);
    }

    std::ostream& incendl(std::ostream& ostr)
    {
        indent(ostr) += 2;
        return ostr << iendl;
    }

    std::ostream& decendl(std::ostream& ostr)
    {
        indent(ostr) -= 2;
        return ostr << iendl;
    }

}
