
namespace bson
{
    inline const std::string& BaseElement::key_get() const
    {
        return key_;
    }

    inline BaseElement::Type BaseElement::type_get() const
    {
        return type_;
    }

}
