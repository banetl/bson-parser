#include <iostream>
#include <memory>

#include "binstring.hh"
#include "codew.hh"

namespace bson
{
    CodeW::CodeW(int32_t length, const BinString& str, const Document& doc)
        : length_(length)
    {
        str_ = std::make_unique<BinString>(str);
        doc_ = std::make_unique<Document>(doc);
    }

    std::ostream& CodeW::dump(std::ostream& ostr) const
    {
        ostr << "Code w/ scope: " << std::endl
             << "\t" "length: " << length_ << std::endl
             << "\t" "Binary string: " << *str_ << std::endl
             << "\t" "Document: " << *doc_ << std::endl;
        return ostr;
    }

    std::ostream& operator<<(std::ostream& ostr, const CodeW& code)
    {
        return code.dump(ostr);
    }
}
