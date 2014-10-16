#pragma once
#include "Json.hpp"
#include <boost/spirit/include/support_utree.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi_list.hpp>
#include <boost/assert.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
namespace json {

    Json getJsonFromFile(std::string filename)
    {
        using namespace grammar;
        std::ifstream in(filename, std::ios_base::in);

        if (!in)
        {
            std::cerr << "Error: Could not open input file: "
                    << filename << std::endl;
        }
        std::string storage; // We will read the contents here.
        in.unsetf(std::ios::skipws); // No white space skipping!
        std::copy(
                std::istream_iterator<char>(in),
                std::istream_iterator<char>(),
                std::back_inserter(storage));

        //typedef json_grammar<std::string::const_iterator> json_grammar;
        json_grammar<std::string::const_iterator> grammar; // Our grammar
        Json ast; // Our tree

        using boost::spirit::standard::space;
        std::string::const_iterator iter = storage.begin();
        std::string::const_iterator end = storage.end();

        bool r = phrase_parse(iter, end, grammar, space, ast);

        if (r && iter == end)
        {
            //std::cout << "-------------------------\n";
            //std::cout << "Parsing succeeded\n";
            //std::cout << "-------------------------\n";
            return ast;

        }
    }
    struct find_visitor : public boost::static_visitor<Value>
    {
        using Node = std::string;
        std::deque<Node> nodes;
        Value operator()(Array a) const
        {
            return a;
        }

        Value operator()(Object o)
        {
            std::string searchterm = nodes.front();
            Object::iterator it = o.find(searchterm);
            if(it != o.end())
            {
                if(nodes.empty())
                {
                    return it->second;
                }
                else
                {
                    nodes.pop_front();
                    find_visitor visitor;
                    visitor.nodes = nodes;
                    return boost::apply_visitor(visitor, it->second);
                }
            }
        }

        Value operator()(Value v) const
        {
            switch (v.which()) {
                case 1: {
                    find_visitor visitor;
                    visitor.nodes = nodes;
                    return boost::apply_visitor(visitor, v);
                    break;
                }
                default:
                    return v;
            }
        }
    };
    Value get_member(std::string path, Json json)
    {

        using boost::spirit::qi::parse;
        using boost::spirit::qi::standard::space;
        using boost::spirit::qi::alpha;
        using boost::spirit::qi::int_;
        using boost::spirit::qi::standard::char_;
        using Node = std::string;
        std::deque<Node> nodes;

        std::string::const_iterator iter = path.begin();
        std::string::const_iterator end = path.end();
        bool r = parse(iter, end, (*alpha % '.'), nodes);
        find_visitor visitor;
        visitor.nodes = nodes;
        return boost::apply_visitor(visitor, json);
    }


    struct print_visitor : public boost::static_visitor<void> {
        void operator()(Array a) const {
            std::cout << "[";
            for (auto &i : a) {
                boost::apply_visitor(print_visitor(), i);
                std::cout << ",";
            }
            std::cout << "]" << std::endl;
        }

        void operator()(Object o) const {
            std::cout << "{";
            for (auto &i : o) {
                std::cout << i.first;
                std::cout << ":";
                boost::apply_visitor(print_visitor(), i.second);
                std::cout << ",";
            }
            std::cout << "}" << std::endl;
        }

        void operator()(Value v) const {
            switch (v.which()) {
                case 0:
                    std::cout << boost::get<bool>(v);
                    break;
                case 1:
                    boost::apply_visitor(print_visitor(), v);
                    break;
                case 2:
                    boost::apply_visitor(print_visitor(), v);
                    break;
                case 3:
                    std::cout << boost::get<int>(v);
                    break;
                case 4:
                    std::cout << boost::get<std::string>(v);
                    break;
            }


        }
    };
}