#include <any>
#include <iostream>
#include <variant>
#include <vector>

#include "document.hh"
#include "utils.hh"

namespace bson
{
    Document::Document(int32_t length, const vect_type& list)
        : length_(length),
          list_(list)
    {

    }

    std::ostream& Document::dump(std::ostream& ostr) const
    {
        ostr << "Document:" << utils::incendl
             << "length: " << length_ << utils::iendl
             << "content: " << utils::incendl;

        for (auto i : list_)
            ostr << *i << utils::iendl;
        // Reset indentation after the document
        utils::indent(ostr) -= 2;
        ostr << utils::iendl;
        return ostr;
    }

    std::ostream& operator<<(std::ostream& ostr, const Document& doc)
    {
        return doc.dump(ostr);
    }
}
