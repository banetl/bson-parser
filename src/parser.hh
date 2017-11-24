#pragma once

#include <memory>
#include <vector>
#include <variant>

namespace bson
{

    using terminal = std::variant<int8_t, int32_t, int64_t, uint64_t,
                                  double, long double>;

    /* Possible values of the Element template:
     * - double
     * - bson::BinString
     * - bson::Document
     * - bson::Binary
     * - std::array<12, uint8_t>
     * - uint8_t
     * - int64_t
     * - std::pair<std::string, std::string>
     * - std::pair<bson::BinString, std::array<12, uint8_t>>
     * - bson::CodeW
     * - int32_t
     * - uint64_t
     * - long double
     */

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
