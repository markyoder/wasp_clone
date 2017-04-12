#ifndef WASP_UTILS_H
#define WASP_UTILS_H
#include "waspcore/wasp_bug.h"
#include <cmath>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdio.h> // windows exponent configure

namespace wasp{
    /**
     * @brief strip_quotes removes single or double quotes
     * @param s the string to have the quotes removes from.
     * @return a string with 1 set of single or double quotes removed
     */
    std::string strip_quotes( const std::string & s);

    /**
     * @brief trim removes the given character set leading and trailing from the given string
     * @param s the string to trim potential prefix and suffix characters
     * @param char_set the set of characters to be remove
     * @return the string with all leading and trailing character set removed
     */
    std::string trim(  std::string s, const std::string& char_set);
    /**
     * @brief xml_escape_data replaces string with escaped versions of the five
     * characters that must be escaped in XML document data ( &, \, ", <, > )
     * to be used on xml data
     * @param src the string in which to have the characters escaped
     * @return a string with characters escaped
     */
    std::string xml_escape_data(const std::string& src);
    /**
     * @brief xml_escape_name replaces string with versions that will parse
     * as node names in xml
     * to be used on xml node names
     * @param src the string in which to have the characters replaced
     * @return a string with characters replaced
     */
    std::string xml_escape_name(const std::string& src);

    /**
     * @brief to_type acquire the data typed as the requested type
     * @param result the typed result
     * @param ok optional boolean return value indicating if conversion was successful.
     */
    template<typename T>
    void to_type(T & result
                 , const std::string & data
                 , bool * ok=nullptr)
    {
        std::stringstream str;
        str<< data;
        str>> result;
        if( ok ) *ok = !(str.bad() || str.fail());
    }
    /**
     *Specialization on string so as to avoid whitespace issues in stream operator>>
     */
    template<>
    inline void to_type<std::string>(std::string & result
                              ,const std::string & data
                              , bool * ok)
    {
        result = data;
        if( ok ) *ok = true;
    }

    template<typename T>
    static std::string to_string(T v, bool * ok=nullptr){
        std::stringstream s;
        s<<v;
        if( ok ) *ok = !(s.bad() || s.fail());
        return s.str();
    }

    /**
     * @brief to_xml walk the given node and emit xml elements into out
     * @param node the node to convert to xml
     * @param out the stream to emit the xml
     * @param emit_decorative indicates whether to emit decorative nodes to xml stream
     * @param space amount of whitespace to prefix to a line
     */
    template<class TAdapter>
    inline void to_xml(const TAdapter& node, std::ostream & out, bool emit_decorative=true, std::string space="")
    {
        bool decorative = node.is_decorative();
        if( decorative && !emit_decorative ) return;
        size_t child_count = node.child_count();
        // print element name and location
        out<<space<<"<"<<xml_escape_name(node.name());
        // capture location if it is a leaf
        if( child_count == 0 ) out<<" loc=\""<<node.line()<<"."<<node.column()<<"\"";
        if( decorative ) out<<" dec=\""<<std::boolalpha<<decorative<<"\"";
        out<<">";
        if( child_count == 0 ) out<<xml_escape_data(node.data());
        else out<<std::endl;
        // recurse into each child
        for( size_t i = 0; i < child_count; ++i )
        {
            to_xml(node.child_at(i),out, emit_decorative, space+"  ");
        }

        // close the element
        if( child_count > 0 ) out<<space;
        out<<"</"<<xml_escape_name(node.name())<<">"<<std::endl;
    }

    /**
     * @brief wildcard_string_match
     * @param first wildcarded pattern to match
     * @param second literal string to determine match
     * @return true, iff, second matches first
     * NOTE: gratefully acquired from :
     * http://www.geeksforgeeks.org/wildcard-character-matching/
     */
    inline bool wildcard_string_match(const char *first, const char * second)
    {
        // If we reach at the end of both strings, we are done
        if (*first == '\0' && *second == '\0')
            return true;

        // Make sure that the characters after '*' are present
        // in second string. This function assumes that the first
        // string will not contain two consecutive '*'
        if (*first == '*' && *(first+1) != '\0' && *second == '\0')
            return false;

        // If the first string contains '?', or current characters
        // of both strings match
        if (*first == '?' || *first == *second)
            return wildcard_string_match(first+1, second+1);

        // If there is *, then there are two possibilities
        // a) We consider current character of second string
        // b) We ignore current character of second string.
        if (*first == '*')
            return wildcard_string_match(first+1, second)
                    || wildcard_string_match(first, second+1);
        return false;
    }   
    template<class TV>
    std::string info( const TV & view )
    {
        if( view.is_null() ) return "@TreeView(null)";
        else return "@TreeView(l="+std::to_string(view.line())
                +","+std::to_string(view.column())
                +": t="+std::to_string(view.tree_node_index())
                +", i"+std::to_string(view.type())
                +", n'"+view.name()+"'"
                +")";
    }
}
#endif
