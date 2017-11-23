
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
        ostr << "Element:" << std::endl
             << "\t" "type: " << this->get_type_string(type_) << std::endl
             << "\t" "key: " << key_ << std::endl
             << "\t" "value: " << val_ << std::endl;
        /* TODO add constexpr check of strange types */
        return ostr;
    }

}
