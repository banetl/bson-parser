#pragma once

#include <iostream>
#include <string>

#include "base-element.hh"

namespace bson
{

    template<typename value>
    class Element : public BaseElement
    {
    public:
        Element(BaseElement::Type type, const std::string& key, const value& val);
        std::ostream& dump(std::ostream& stream) const;
        const value& value_get() const;

    private:
        const value val_;
    };

}

#include "element.hxx"
