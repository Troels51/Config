#include <iostream>
#define BOOST_SPIRIT_DEBUG
#include "Grammar.hpp"
#include "Json.hpp"
#include "JsonUtility.hpp"
#include <boost/spirit/include/qi.hpp>
#include <fstream>

using namespace std;
#define FILENAME "/home/troels/Documents/Config/test/jsontest.json"
int
main()
{
    using namespace json;
    std::cout << "Testing json" << std::endl;
    char const* filename;
    Json json = getJsonFromFile(FILENAME);
    //Testing get_member
    json::Value title;
    title = get_member("glossary.GlossDiv.title" ,json);
    boost::apply_visitor(json::print_visitor(), title);


    return 0;
}