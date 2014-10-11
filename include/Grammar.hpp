/** Grammar for json, based on http://www.ietf.org/rfc/rfc4627.txt **/
#include <boost/spirit/include/qi.hpp>
#define BOOST_SPIRIT_UNICODE

namespace qi = boost::spirit::qi;
template <typename Iterator>
struct json : qi::grammar<Iterator, unsigned()>
{
    json() : json::base_type(json)
    {
        using qi::eps;
        using qi::lit;
        using qi::_val;
        using qi::_1;
        using boost::spirit::standard::char_; //TODO: json is unicode, spirit may support it
        whitespace   = char(' ') | char('\t') | char('\r') | char('\n');
        begin_array  = "[";
        end_array    = "]";
        begin_object = "{";
        end_object   = "}";
        name_separator  = ":";
        value_separator = ",";

        json = whitespace;


    }

    qi::rule<Iterator, string()> whitespace;
    qi::rule<Iterator, json()> begin_array;
    qi::rule<Iterator, json()> end_array;
    qi::rule<Iterator, json()> begin_object;
    qi::rule<Iterator, json()> end_object;
    qi::rule<Iterator, json()> name_separator;
    qi::rule<Iterator, json()> value_separator;


    qi::rule<Iterator, json()> json;


};