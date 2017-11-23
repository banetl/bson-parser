#include <memory>
#include <vector>

#include "base-element.hh"
#include "document.hh"
#include "element.hh"
#include "parser.hh"

namespace bson
{
    Parser::Parser(const std::vector<char>& data)
        : data_(data),
          index_(0)
    {
    }

    const std::unique_ptr<Document> Parser::parse() const
    {
        // FIXME
        auto doc = Document(0, std::vector<BaseElement>());
        auto m = std::make_unique<Document>(doc);
        return m;
    }
}
