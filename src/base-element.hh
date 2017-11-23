#pragma once

#include <iostream>
#include <string>

namespace bson
{

    class BaseElement
    {
    public:
        enum class Type
        {
            bfp, // 64-bit binary floating point
            str, // UTF-8 string
            doc, // Embedded document
            array, // Array
            bdata, // Binary data
            undef, // Undefined
            oid, // ObjectId
            bf, // Boolean false
            bt, // Boolean true
            date, // UTC datetime
            null, // Null value
            regex, // Regular expression
            dbp, // DBPointer
            jvs, // JavaScript code
            symbol, // Symbol
            jvsg, // Javascript code global scope
            i32, // 32-bit integer
            time, // Timestamp
            i64, // 64-bit integer
            d128, // 128-bit decimal floating point
            min, // Min key
            max // Max key
        };

    public:
        BaseElement(BaseElement::Type type, const std::string key);
        virtual ~BaseElement() {};
        virtual std::ostream& dump(std::ostream& stream) const;
        const std::string& key_get() const;
        BaseElement::Type type_get() const;

    protected:
        std::string get_type_string(BaseElement::Type) const;

    protected:
        BaseElement::Type type_;
        const std::string key_;
    };

    std::ostream& operator<<(std::ostream& ostr, const BaseElement& elt);


}
