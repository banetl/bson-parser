#pragma once

#include <any>
#include <iostream>
#include <variant>
#include <vector>

#include "base-element.hh"

namespace bson
{
    class Document
    {
        using vect_type = std::vector<BaseElement>;

    public:
        Document(int32_t length, const vect_type& list);
        std::ostream& dump(std::ostream& stream) const;
        int32_t length_get() const;
        const vect_type& list_get() const;

    private:
        int32_t length_;
        const vect_type list_;
    };

    std::ostream& operator<<(std::ostream& ostr, const Document& doc);
}
