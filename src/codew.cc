#include <iostream>
#include <memory>

#include "binstring.hh"
#include "codew.hh"
#include "utils.hh"

namespace bson
{
    CodeW::CodeW(int32_t length, std::shared_ptr<BinString> str,
                 std::shared_ptr<Document> doc)
        : length_(length),
        str_(str),
        doc_(doc)
    {
    }

    std::ostream& CodeW::dump(std::ostream& ostr) const
    {
        ostr << "Code w/ scope: " << utils::incendl
             << "length: " << length_ << utils::iendl
             << "Binary string: " << *str_ << utils::iendl
             << "Document: " << *doc_ << utils::decendl;
        return ostr;
    }

    std::ostream& operator<<(std::ostream& ostr, const CodeW& code)
    {
        return code.dump(ostr);
    }
}
