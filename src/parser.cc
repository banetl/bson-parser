#include <map>
#include <memory>
#include <vector>

#include "base-element.hh"
#include "binary.hh"
#include "codew.hh"
#include "document.hh"
#include "element.hh"
#include "parser.hh"

namespace bson
{
    Parser::Parser(const std::vector<unsigned char>& data)
        : data_(data),
          index_(0)
    {
    }

    std::shared_ptr<Document> Parser::parse()
    {
        auto length = parse_terminal<int32_t>();
        std::vector<std::shared_ptr<BaseElement>> vect;
        auto last = index_ + length - sizeof(int32_t) - 1;

        while (index_ < last)
            vect.push_back(parse_element());

        if (index_ != last && data_[index_] != '\x00')
            throw std::runtime_error("Bad bson file input");

        // Remove the last '\x00' of the doc:
        index_++;
        auto doc = Document(length, vect);
        return std::make_shared<Document>(doc);
    }

    static BaseElement::Type get_elt_type(unsigned char value)
    {
        const std::map<unsigned char, BaseElement::Type> type_map
        {
            { '\x01', BaseElement::Type::bfp },
            { '\x02', BaseElement::Type::str },
            { '\x03', BaseElement::Type::doc },
            { '\x04', BaseElement::Type::array },
            { '\x05', BaseElement::Type::bdata },
            { '\x06', BaseElement::Type::undef },
            { '\x07', BaseElement::Type::oid },
            { '\x08', BaseElement::Type::bf },
        //  { '\x08', BaseElement::Type::bt },
            { '\x09', BaseElement::Type::date },
            { '\x0A', BaseElement::Type::null },
            { '\x0B', BaseElement::Type::regex },
            { '\x0C', BaseElement::Type::dbp },
            { '\x0D', BaseElement::Type::jvs },
            { '\x0E', BaseElement::Type::symbol },
            { '\x0F', BaseElement::Type::jvsg },
            { '\x10', BaseElement::Type::i32 },
            { '\x11', BaseElement::Type::time },
            { '\x12', BaseElement::Type::i64 },
            { '\x13', BaseElement::Type::d128 },
            { '\xFF', BaseElement::Type::min },
            { '\x7F', BaseElement::Type::max },
        };
        auto it = type_map.find(value);
        if (it == type_map.end())
            throw std::runtime_error("Bad bson file input");
        return it->second;
    }

    std::shared_ptr<BaseElement> Parser::parse_element()
    {
        auto type = data_[index_++];
        auto elt_type = get_elt_type(type);
        const std::string key = parse_cstring();

        switch (elt_type)
        {
        case BaseElement::Type::bfp:
            return parse_and_return<double>(elt_type, key);
        case BaseElement::Type::str:
        case BaseElement::Type::jvs:
        case BaseElement::Type::symbol:
        {
            auto value = parse_binstring();
            auto elem = Element<std::shared_ptr<BinString>>(elt_type, key, value);
            return std::make_shared<Element<std::shared_ptr<BinString>>>(elem);
        }
        case BaseElement::Type::doc:
        case BaseElement::Type::array:
        {
            auto value = parse();
            auto elem = Element<std::shared_ptr<Document>>(elt_type, key, value);
            return std::make_shared<Element<std::shared_ptr<Document>>>(elem);
        }
        case BaseElement::Type::bdata:
        {
            auto value = parse_binary();
            auto elem = Element<std::shared_ptr<Binary>>(elt_type, key, value);
            return std::make_shared<Element<std::shared_ptr<Binary>>>(elem);
        }
        case BaseElement::Type::undef:
        case BaseElement::Type::null:
        case BaseElement::Type::min:
        case BaseElement::Type::max:
            return std::make_shared<BaseElement>(BaseElement(elt_type, key));
        case BaseElement::Type::oid:
        {
            std::array<uint8_t, 12> value;
            for (size_t i = 0; i < 12; ++i)
                value[i] = data_[index_ + i];
            index_ += 12;
            auto elem = Element<id_type>(elt_type, key, value);
            return std::make_shared<Element<id_type>>(elem);
        }
        case BaseElement::Type::bf:
        {
            auto boolean = data_[index_++];
            auto elt_type = boolean ? BaseElement::Type::bt : BaseElement::Type::bf;
            return std::make_shared<BaseElement>(BaseElement(elt_type, key));
        }
        case BaseElement::Type::date:
        case BaseElement::Type::i64:
            return parse_and_return<int64_t>(elt_type, key);
        case BaseElement::Type::regex:
        {
            auto val1 = parse_cstring();
            auto val2 = parse_cstring();
            auto value = regex_type(val1, val2);
            auto elem = Element<regex_type>(elt_type, key, value);
            return std::make_shared<Element<regex_type>>(elem);
        }
        case BaseElement::Type::dbp:
        {
            auto val1 = parse_binstring();
            std::array<uint8_t, 12> val2;
            for (size_t i = 0; i < 12; ++i)
                val2[i] = data_[index_ + i];
            index_ += 12;
            auto value = dbptr_type(val1, val2);
            auto elem = Element<dbptr_type>(elt_type, key, value);
            return std::make_shared<Element<dbptr_type>>(elem);
        }
        case BaseElement::Type::jvsg:
        {
            auto value = parse_codew();
            auto elem = Element<std::shared_ptr<CodeW>>(elt_type, key, value);
            return std::make_shared<Element<std::shared_ptr<CodeW>>>(elem);
        }
        case BaseElement::Type::i32:
            return parse_and_return<int32_t>(elt_type, key);
        case BaseElement::Type::time:
            return parse_and_return<uint64_t>(elt_type, key);
        case BaseElement::Type::d128:
            return parse_and_return<long double>(elt_type, key);
        default:
            throw std::runtime_error("Bad bson file input");
        }
    }


    const std::string Parser::parse_cstring()
    {
        std::string res = "";
        while (data_[index_] != '\x00')
        {
            res += data_[index_];
            index_++;
        }
        res += data_[index_++];
        return res;
    }

    const std::basic_string<uint8_t> Parser::parse_string(size_t len)
    {
        std::basic_string<uint8_t> res;
        for (size_t i = 0; i < len; ++i)
        {
            res += data_[index_];
            index_++;
        }
        return res;
    }

    std::shared_ptr<BinString> Parser::parse_binstring()
    {
        int32_t length = parse_terminal<int32_t>();
        auto last = length + index_;
        auto str_data = parse_string(length);

        if (index_ != last)
            throw std::runtime_error("Bad bson file input");

        return std::make_shared<BinString>(BinString(length, str_data));
    }

    std::shared_ptr<Binary> Parser::parse_binary()
    {
        int32_t length = parse_terminal<int32_t>();
        auto subtype = data_[index_++];
        auto last = index_ + length;

        const std::map<unsigned char, Binary::Type> type_map
        {
            { '\x00', Binary::Type::generic },
            { '\x01', Binary::Type::function },
            { '\x02', Binary::Type::old },
            { '\x03', Binary::Type::olduuid },
            { '\x04', Binary::Type::uuid },
            { '\x05', Binary::Type::md5 },
            { '\x80', Binary::Type::user }
        };
        auto type = type_map.find(subtype);
        Binary::Type real_type;
        if (type != type_map.end())
            real_type = type->second;
        else if (type == type_map.end() && subtype >= 0x80)
            real_type = Binary::Type::user;
        else
            throw std::runtime_error("Bad bson file input");

        auto data = parse_string(length);

        if (index_ != last)
            throw std::runtime_error("Bad bson file input");

        return std::make_shared<Binary>(Binary(length, real_type, data));
    }


    std::shared_ptr<CodeW> Parser::parse_codew()
    {
        int32_t length = parse_terminal<int32_t>();
        auto last = index_ + length - sizeof(int32_t);
        auto str = parse_binstring();
        auto doc = parse();

        if (index_ != last)
            throw std::runtime_error("Bad bson file input");

        return std::make_shared<CodeW>(CodeW(length, str, doc));
    }
}
