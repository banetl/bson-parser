#include <any>
#include <iostream>
#include <variant>
#include <vector>

#include "document.hh"

namespace bson
{
    Document::Document(int32_t length, const vect_type& list)
        : length_(length),
          list_(list)
    {

    }

    std::ostream& Document::dump(std::ostream& ostr) const
    {
        ostr << "Document:" << std::endl
             << "\t" "length: " << length_ << std::endl
             << "\t" "content: " << std::endl;

        for (auto i : list_)
            ostr << "\t\t" << i << std::endl;

        return ostr;
    }

    std::ostream& operator<<(std::ostream& ostr, const Document& doc)
    {
        return doc.dump(ostr);
    }
}
