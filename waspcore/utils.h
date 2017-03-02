#ifndef WASP_UTILS_H
#define WASP_UTILS_H
#include <string>
#include <sstream>
#include "wasp_node.h"
namespace wasp{
    /**
     * @brief strip_quotes removes single or double quotes
     * @param s the string to have the quotes removes from.
     * @return a string with 1 set of single or double quotes removed
     */
    std::string strip_quotes( const std::string & s);  
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
}
#endif
