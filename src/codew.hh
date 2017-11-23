#pragma once

#include <iostream>
#include <memory>

#include "binstring.hh"
#include "document.hh"

namespace bson
{
    class CodeW
    {
    public:
        CodeW(int32_t length, const BinString& str, const Document& doc);
        std::ostream& dump(std::ostream& stream) const;
        const std::unique_ptr<BinString>& str_get() const;
        const std::unique_ptr<Document>& doc_get() const;
        int32_t length_get() const;

    private:
        int32_t length_;
        std::unique_ptr<BinString> str_;
        std::unique_ptr<Document> doc_;
    };

    std::ostream& operator<<(std::ostream& ostr, const CodeW& code);
}

#include "codew.hxx"
