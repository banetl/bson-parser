
namespace bson
{
    inline const std::unique_ptr<BinString>& CodeW::str_get() const
    {
        return str_;
    }

    inline const std::unique_ptr<Document>& CodeW::doc_get() const
    {
        return doc_;
    }

    inline int32_t CodeW::length_get() const
    {
        return length_;
    }

}
