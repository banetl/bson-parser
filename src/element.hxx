#include <type_traits>

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
        // Replace by BaseElement::dump
        ostr << "Element:" << std::endl
             << "\t" "type: " << this->get_type_string(type_) << std::endl
             << "\t" "key: " << key_ << std::endl;
        if constexpr (std::is_same<id_type, value>::value)
        {
            ostr << "\t" "value: ";
            for (auto i : val_)
                ostr << i;
            ostr << std::endl;
        }
        else if constexpr (std::is_same<regex_type, value>::value)
        {
            ostr << "\t" "pattern: " << val_.first
                 << " options: " << val_.second;
        }
        else if constexpr (std::is_same<dbptr_type, value>::value)
        {
            ostr << "\t" "DBpointer: " << *val_.first << "  ";
            for (auto i : val_.second)
                ostr << i;
            ostr << std::endl;
        }
        else
             ostr << "\t" "value: " << val_ << std::endl;
        return ostr;
    }

}
