#include <iostream>
#include <map>
#include <vector>

#include "binary.hh"

namespace bson
{

    Binary::Binary(int32_t number, Binary::Type type,
                   const std::vector<uint8_t>& data)
        : length_(number),
          type_(type),
          data_(data)
    {
    }

    std::ostream& Binary::dump(std::ostream& ostr) const
    {
        ostr << "Binary:" << std::endl
            << "\t" "length: " << length_ << std::endl
            << "\t" "type:" << get_type_string(type_) << std::endl;
        return ostr;
    }


    std::ostream& operator<<(std::ostream& ostr, const Binary& bin)
    {
        return bin.dump(ostr);
    }


    std::string Binary::get_type_string(Binary::Type e) const
    {
        const std::map<Binary::Type, const std::string> type_to_str
        {
            { Binary::Type::generic, "Generic binary subtype" },
            { Binary::Type::function, "Function" },
            { Binary::Type::old, "Binary (Old)" },
            { Binary::Type::olduuid, "UUID (Old)" },
            { Binary::Type::uuid, "UUID" },
            { Binary::Type::md5, "MD5" },
            { Binary::Type::user, "User defined" }
        };
        auto it = type_to_str.find(e);
        return (it != type_to_str.end()) ? it->second : "Error";
    }

}
