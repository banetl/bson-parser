#pragma once

#include <iostream>
#include <string>

namespace bson
{
    class BinString
    {
    public:
        BinString(int32_t length, const std::basic_string<uint8_t>& data);
        std::ostream& dump(std::ostream& stream) const;
        const std::basic_string<uint8_t>& data_get() const;
        int32_t length_get() const;

    private:
        int32_t length_;
        const std::basic_string<uint8_t> data_;
    };

    std::ostream& operator<<(std::ostream& ostr, const BinString& str);
}

#include "binstring.hxx"
