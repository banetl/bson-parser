#include <type_traits>

#include "utils.hh"

namespace bson
{

    template<typename value>
    Element<value>::Element(Element::Type type, const std::string& key,
                     const value& val)
        : BaseElement(type, key),
          val_(val)
    {
    }

    template<typename value>
    inline const value& Element<value>::value_get() const
    {
        return val_;
    }

    template<typename value>
    std::ostream& Element<value>::dump(std::ostream& ostr) const
    {
        BaseElement::dump(ostr);
        // Special treatment for hard to print values
        if constexpr (std::is_same<id_type, value>::value)
        {
            ostr << "value: ";
            for (auto i : val_)
                ostr << i;
        }
        else if constexpr (std::is_same<regex_type, value>::value)
        {
            ostr << "pattern: " << val_.first
                 << "\t" " options: " << val_.second;
        }
        else if constexpr (std::is_same<dbptr_type, value>::value)
        {
            ostr << "DBpointer: " << *val_.first << "\t";
            for (auto i : val_.second)
                ostr << i;
        }
        else
             ostr << "value: " << val_;
        ostr << utils::iendl;
        return ostr;
    }

}
