
#include <map>
#include <vector>
#include <string>
#include <boost/variant/variant_fwd.hpp>

namespace json
{
    typedef boost::make_recursive_variant<bool, std::map<std::string, boost::recursive_variant_> , std::vector<boost::recursive_variant_>, int, std::string>::type Value;
    typedef std::vector<Value> Array;
    typedef std::map<std::string, Value> Object;
    typedef boost::variant<Array, Object> Json;


//    typedef boost::variant<bool, boost::recursive_wrapper<Object>,boost::recursive_wrapper<Array> , int, std::string> Value;
//    struct Object
//    {
//        Object()
//        {
//        }
//        Object(Value value)
//        {
//            mapping = boost::get<Object>(value).mapping;
//        }
//        push_back()
//        std::map<std::string, Value> mapping;
//    };
//    struct Array
//    {
//        Array()
//        {
//        }
//        Array(Value value)
//        {
//            valueVector = boost::get<Array>(value).valueVector;
//        }
//        std::vector<Value> valueVector;
//    };

}

//BOOST_FUSION_ADAPT_STRUCT(
//        json::Json,
//(boost::optional<json::Array>, maybe_array)
//(boost::optional<json::Object>, maybe_object))