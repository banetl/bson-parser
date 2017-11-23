#include <map>
#include <string>

#include "base-element.hh"

namespace bson
{

    BaseElement::BaseElement(BaseElement::Type type, const std::string key)
        : type_(type),
          key_(key)
    {
    }

    std::string BaseElement::get_type_string(BaseElement::Type e) const
    {
        const std::map<BaseElement::Type, const std::string> type_to_str
        {
            { BaseElement::Type::bfp, "64-bit binary floating point" },
            { BaseElement::Type::str, "UTF-8 string" },
            { BaseElement::Type::doc, "Embedded document" },
            { BaseElement::Type::array, "Array" },
            { BaseElement::Type::bdata, "Binary data" },
            { BaseElement::Type::undef, "Undefined (value) — Deprecated" },
            { BaseElement::Type::oid, "ObjectId" },
            { BaseElement::Type::bf, "Boolean \"false\"" },
            { BaseElement::Type::bt, "Boolean \"true\"" },
            { BaseElement::Type::date, "UTC datetime" },
            { BaseElement::Type::null, "Null value" },
            { BaseElement::Type::regex, "Regular expression" },
            { BaseElement::Type::dbp, "DBPointer" },
            { BaseElement::Type::jvs, "JavaScript code" },
            { BaseElement::Type::symbol, "Symbol" },
            { BaseElement::Type::jvsg, "JavaScript code w/ scope" },
            { BaseElement::Type::i32, "32-bit integer" },
            { BaseElement::Type::time, "Timestamp" },
            { BaseElement::Type::i64, "64-bit integer" },
            { BaseElement::Type::d128, "128-bit decimal floating point" },
            { BaseElement::Type::min, "Min key" },
            { BaseElement::Type::max, "Max key" },
        };
        auto it = type_to_str.find(e);
        return (it != type_to_str.end()) ? it->second : "Error";
    }

    std::ostream& BaseElement::dump(std::ostream& ostr) const
    {
        ostr << "Element:" << std::endl
             << "\t" "type: " << this->get_type_string(type_) << std::endl
             << "\t" "key: " << key_ << std::endl;
        return ostr;
    }



    std::ostream& operator<<(std::ostream& ostr, const BaseElement& elt)
    {
        return elt.dump(ostr);
    }


}
