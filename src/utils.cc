#include <iostream>

#include "utils.hh"

namespace utils
{

    std::ostream& iendl(std::ostream& ostr)
    {
        ostr << std::endl;
        char fill = ostr.fill('\t');
        return ostr << std::setw(indent(ostr))
            << ""
            << std::setfill(fill);
    }

    std::ostream& incendl(std::ostream& ostr)
    {
        indent(ostr)++;
        return ostr << iendl;
    }

    std::ostream& decendl(std::ostream& ostr)
    {
        indent(ostr)--;
        return ostr << iendl;
    }

}
