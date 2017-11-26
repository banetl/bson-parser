#include <iostream>
#include <string>

#include "binstring.hh"
#include "utils.hh"

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
        ostr << "Binary String:" << utils::incendl
             << "length: " << +length_ << utils::iendl
             << "value: ";
        for (auto i : data_)
            ostr << "\\x" << std::hex << +i;
        ostr << utils::decendl;
        return ostr;
    }

    std::ostream& operator<<(std::ostream& ostr, const BinString& str)
    {
        return str.dump(ostr);
    }
}
