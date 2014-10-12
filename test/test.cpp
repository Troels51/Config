#include <iostream>
#include "Grammar.hpp"
#include <boost/spirit/include/qi.hpp>
#include <fstream>

using namespace std;
#define FILENAME "jsontest.json"
int
main()
{
    char const* filename;

    std::ifstream in(FILENAME, std::ios_base::in);

    if (!in)
    {
        std::cerr << "Error: Could not open input file: "
                << filename << std::endl;
        return 1;
    }

    std::string storage; // We will read the contents here.
    in.unsetf(std::ios::skipws); // No white space skipping!
    std::copy(
            std::istream_iterator<char>(in),
            std::istream_iterator<char>(),
            std::back_inserter(storage));

    typedef json_grammar<std::string::const_iterator> json_grammar;
    json_grammar xml; // Our grammar
    json::json ast; // Our tree

    using boost::spirit::standard::space;
    std::string::const_iterator iter = storage.begin();
    std::string::const_iterator end = storage.end();
    bool r = phrase_parse(iter, end, xml, space, ast);

    if (r && iter == end)
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << "-------------------------\n";
        //client::mini_xml_printer printer;
        //printer(ast);
        return 0;
    }
    else
    {
        std::string::const_iterator some = iter+30;
        std::string context(iter, (some>end)?end:some);
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "stopped at: \": " << context << "...\"\n";
        std::cout << "-------------------------\n";
        return 1;
    }

    return 0;
}