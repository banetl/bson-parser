#include <algorithm>
#include <cstring>

namespace bson
{

    // Simple functions to factorize the parsing

    template <typename t>
    t Parser::parse_terminal()
    {
        t number = 0;
        std::vector<unsigned char> num(data_.begin() + index_,
                                       data_.begin() + index_ + sizeof(t));
        std::memcpy(&number, &num.front(), sizeof(t));
        index_ += sizeof(t);
        return number;
    }

    template <typename t>
    std::shared_ptr<Element<t>>
    Parser::parse_and_return(BaseElement::Type type, const std::string key)
    {
        t value = parse_terminal<t>();
        return std::make_shared<Element<t>>(Element<t>(type, key, value));
    }

}
