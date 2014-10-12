#include <boost/any.hpp>
#include <map>
#include <vector>
#include <boost/optional.hpp>
#include <string>
namespace json
{
    struct value
    {
        boost::any value;
    };

    struct object
    {
        std::map<std::string, value> map;
    };
    struct array
    {
        std::vector<value> values;
    };
    struct json
    {
        boost::optional<array> maybe_array;
        boost::optional<object> maybe_object;
    };
}
