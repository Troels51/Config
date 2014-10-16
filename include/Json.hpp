#pragma once
#include "Grammar.hpp"
#include <map>
#include <vector>
#include <string>
#include <boost/variant/variant_fwd.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/get.hpp>
#include <iostream>
#include <fstream>
#include <boost/spirit/include/qi.hpp>

namespace json
{
    typedef boost::make_recursive_variant<bool, std::map<std::string, boost::recursive_variant_> , std::vector<boost::recursive_variant_>, int, std::string>::type Value;
    typedef std::vector<Value> Array;
    typedef std::map<std::string, Value> Object;
    typedef boost::variant<Array, Object> Json;

}