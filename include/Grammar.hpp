/** Grammar for json, based on http://www.ietf.org/rfc/rfc4627.txt **/
#include <boost/spirit/include/qi.hpp>
#define BOOST_SPIRIT_UNICODE
#include "Json.hpp"
namespace qi = boost::spirit::qi;
template <typename Iterator>
struct json_grammar : qi::grammar<Iterator, json::json()>
{
    json_grammar() : json_grammar::base_type(json)
    {
        using qi::eps;
        using qi::lit;
        using qi::_val;
        using qi::_1;
        using boost::spirit::standard::char_; //TODO: json is unicode, spirit may support it
        using boost::spirit::standard::digit;
        using boost::spirit::qi::int_;
        whitespace   = char(' ') | char('\t') | char('\r') | char('\n');
        begin_array  = "[";
        end_array    = "]";
        begin_object = "{";
        end_object   = "}";
        name_separator  = ":";
        value_separator = ",";
        member = jstring >> name_separator >> value;
        object = begin_object >> -(member >> *(value_separator >> member)) >> end_object;
        array = begin_array >> -(value >> *(value_separator)) >> end_array;
        number = -(char('-')) >> int_ -(char('.') >> +(digit)) >> -(char('e') >> -(char('-') | char('+')) >> +digit);
        jstring = char('"') >> *char_ >> char('"'); //does not support escaping characters yet
        value = lit("false") | lit("null") | lit("true") | object | array | number | jstring;
        json = object | array;

    }

    qi::rule<Iterator> whitespace;
    qi::rule<Iterator> begin_array;
    qi::rule<Iterator> end_array;
    qi::rule<Iterator> begin_object;
    qi::rule<Iterator> end_object;
    qi::rule<Iterator> name_separator;
    qi::rule<Iterator> value_separator;
    qi::rule<Iterator> object;
    qi::rule<Iterator> array;
    qi::rule<Iterator> number;
    qi::rule<Iterator> jstring;
    qi::rule<Iterator> member;
    qi::rule<Iterator> value;

    qi::rule<Iterator, json::json()> json;


};