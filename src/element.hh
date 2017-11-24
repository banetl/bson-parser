#pragma once

#include <array>
#include <iostream>
#include <utility>
#include <string>

#include "base-element.hh"
#include "binstring.hh"

namespace bson
{
    /* Possible values of the Element template:
     * - double
     * - bson::BinString
     * - bson::Document
     * - bson::Binary
     * - std::array<12, uint8_t>
     * - uint8_t
     * - int64_t
     * - std::pair<std::string, std::string>
     * - std::pair<bson::BinString, std::array<12, uint8_t>>
     * - bson::CodeW
     * - int32_t
     * - uint64_t
     * - long double
     */

    template<typename value>
    class Element : public BaseElement
    {
        // Complex types:
        // -> types that are hard to print and need a special treatment
        using id_type = std::array<uint8_t, 12>;
        using regex_type = std::pair<std::string, std::string>;
        using dbptr_type = std::pair<bson::BinString, id_type>;

    public:
        Element(BaseElement::Type type, const std::string& key, const value& val);
        std::ostream& dump(std::ostream& stream) const;
        const value& value_get() const;

    private:
        const value val_;
    };

}

#include "element.hxx"
