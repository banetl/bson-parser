
namespace bason
{

    inline int32_t Document::length_get() const
    {
        return length_;
    }

    inline const Document::vect_type& Document::list_get() const
    {
        return list_;
    }

}
