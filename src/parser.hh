#pragma once

#include <memory>
#include <vector>
#include <variant>

#include "base-element.hh"
#include "binary.hh"
#include "binstring.hh"
#include "codew.hh"
#include "document.hh"
#include "element.hh"

namespace bson
{

    /* Possible values of the Element template:
     * - double
     * - std::shared_ptr<bson::BinString>
     * - std::shared_ptr<bson::Document>
     * - std::shared_ptr<bson::Binary>
     * - std::array<12, uint8_t>
     * - uint8_t
     * - int64_t
     * - std::pair<std::string, std::string>
     * - std::pair<std::shared_ptr<bson::BinString>, std::array<12, uint8_t>>
     * - std::shared_ptr<bson::CodeW>
     * - int32_t
     * - uint64_t
     * - long double
     */

    class Parser
    {
        // Complex types:
        using id_type = std::array<uint8_t, 12>;
        using regex_type = std::pair<std::string, std::string>;
        using dbptr_type = std::pair<std::shared_ptr<bson::BinString>, id_type>;

    public:
        Parser(const std::vector<unsigned char>& data);
        std::shared_ptr<Document> parse();

    private:
        // Terminal
        // int8_t, int32_t, int64_t, uint64_t, double, long double
        template <typename t>
        t parse_terminal();

        template <typename t>
        std::shared_ptr<Element<t>>
        parse_and_return(BaseElement::Type type, const std::string key);

        const std::string parse_cstring();
        const std::basic_string<uint8_t> parse_string(size_t len);
        std::shared_ptr<BinString> parse_binstring();
        std::shared_ptr<Binary> parse_binary();
        std::shared_ptr<BaseElement> parse_element();
        std::shared_ptr<CodeW> parse_codew();

    private:
        const std::vector<unsigned char> data_;
        size_t index_;
    };
}

#include "parser.hxx"
