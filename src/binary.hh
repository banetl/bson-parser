#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace bson
{

    class Binary
    {
    public:

        enum class Type
        {
            generic, // Generic Binary subtype
            function,
            old,
            olduuid,
            uuid,
            md5,
            user // User defined
        };

    public:
        Binary(int32_t number, Binary::Type type,
               const std::vector<uint8_t>& data);
        std::ostream& dump(std::ostream& stream) const;
        int32_t length_get() const;
        Binary::Type type_get() const;
        const std::vector<uint8_t>& data_get() const;

    private:
        std::string get_type_string(Binary::Type) const;

    private:
        int32_t length_;
        Binary::Type type_;
        const std::vector<uint8_t> data_;
    };

    std::ostream& operator<<(std::ostream& ostr, const Binary& bin);

}

#include "binary.hxx"
