
namespace bson
{

    inline const std::basic_string<uint8_t>& Binary::data_get() const
    {
        return data_;
    }

    inline int32_t Binary::length_get() const
    {
        return length_;
    }

    inline Binary::Type Binary::type_get() const
    {
        return type_;
    }

}
