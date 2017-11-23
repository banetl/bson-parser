
namespace bson
{
    inline const std::basic_string<uint8_t>& BinString::data_get() const
    {
        return data_;
    }

    inline int32_t BinString::length_get() const
    {
        return length_;
    }

}
