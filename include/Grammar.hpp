/** Grammar for json, based on http://www.ietf.org/rfc/rfc4627.txt **/
#include <boost/spirit/include/qi.hpp>
#include "Json.hpp"
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant/variant_fwd.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/foreach.hpp>
#include <boost/fusion/include/adapted.hpp>

namespace qi = boost::spirit::qi;
namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
template <typename Iterator>
struct json_grammar : qi::grammar<Iterator, json::Json()>
{
    json_grammar() : json_grammar::base_type(json, "json")
    {
        using qi::on_error;
        using qi::fail;
        using qi::eps;
        using qi::lit;
        using qi::_val;
        using qi::_1;
        using qi::_2;
        using namespace qi::labels;

        using phoenix::construct;
        using phoenix::val;
        using phoenix::push_back;

        using boost::spirit::standard::char_; //TODO: json is unicode, spirit may support it
        using boost::spirit::standard::digit;
        using boost::spirit::qi::int_;
        whitespace   = *(char_(' ') | char_('\t') | char_('\r') | char_('\n'));
        begin_array  = whitespace >> char_('[') >> whitespace;
        end_array    = whitespace >> char_(']') >> whitespace;
        begin_object = whitespace >> char_('{') >> whitespace;
        end_object   = whitespace >> char_('}') >> whitespace;
        name_separator  = whitespace >> char_(':') >> whitespace;
        value_separator = whitespace >> char_(',') >> whitespace;
        member = jstring > name_separator > value;// [_val = construct< std::pair<std::string, json::value > >(_1, _2)];
        object = begin_object > -(member >> *(value_separator >> member)) > end_object;// [push_back(_val,_1)];
        array = begin_array > -(value >> *(value_separator >> value)) > end_array;
        number = -(char_('-')) >> int_ -(char_('.') >> +(digit)) >> -(char_('e') >> -(char_('-') | char_('+')) >> +digit);
        unesc_char.add("\\a", '\a')("\\b", '\b')("\\f", '\f')("\\n", '\n')
                ("\\r", '\r')("\\t", '\t')("\\v", '\v')("\\\\", '\\')
                ("\\\'", '\'')("\\\"", '\"');

        jstring = '"' >> *(unesc_char | qi::alnum | qi::space | "\\x" >> qi::hex) >> '"';
        value = lit("false") | lit("null") | lit("true") | object | array | number | jstring;
        json = object | array;

        json.name("json");
        begin_array.name("begin_array");
        begin_object.name("begin_object");
        object.name("object");
        value.name("value");
        whitespace.name("whitespace");
        end_array.name("end_array");
        end_object.name("end_object");
        name_separator.name("name_separator");
        value_separator.name("value_separator");
        number.name("number");
        jstring.name("jstring");
        member.name("member");

        on_error<fail>
                (
                        json,
                        std::cout
                                << val("Error! Expecting ")
                                << _4                               // what failed?
                                << val(" here: \"")
                                << construct<std::string>(_3, _2)   // iterators to error-pos, end
                                << val("\"")
                                << std::endl
                );
    }
    qi::rule<Iterator> whitespace;
    qi::rule<Iterator> begin_array;
    qi::rule<Iterator> end_array;
    qi::rule<Iterator> begin_object;
    qi::rule<Iterator> end_object;
    qi::rule<Iterator> name_separator;
    qi::rule<Iterator> value_separator;
    qi::rule<Iterator, json::Object()> object;
    qi::rule<Iterator, json::Array()> array;
    qi::rule<Iterator, int()> number;
    qi::rule<Iterator, std::string()> jstring;
    qi::symbols<char const, char const> unesc_char;
    qi::rule<Iterator, std::pair<std::string, json::Value>() > member;
    qi::rule<Iterator, json::Value()> value;

    qi::rule<Iterator, json::Json()> json;


};

