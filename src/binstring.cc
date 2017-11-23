#include <iostream>
#include <string>

#include "binstring.hh"

namespace bson
{

    BinString::BinString(int32_t length,
                         const std::basic_string<uint8_t>& data)
        : length_(length),
          data_(data)
    {
    }

    std::ostream& BinString::dump(std::ostream& ostr) const
    {
        ostr << "Binary String:"
             << "\t" "length: "
             << length_
             << std::endl;
        return ostr;
    }

    std::ostream& operator<<(std::ostream& ostr, const BinString& str)
    {
        return str.dump(ostr);
    }
}
