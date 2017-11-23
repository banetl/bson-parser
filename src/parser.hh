#pragma once

#include <memory>
#include <vector>
#include <variant>

namespace bson
{

    using terminal = std::variant<int8_t, int32_t, int64_t, uint64_t,
                                  double, long double>;

    class Parser
    {
    public:
        Parser(const std::vector<char>& data);
        const std::unique_ptr<Document> parse() const;

    private:
        const std::vector<char> data_;
        size_t index_;
    };
}
