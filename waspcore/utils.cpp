#include "waspcore/utils.h"
namespace wasp{
std::string strip_quotes( const std::string& src )
{
    std::string s = src;
    // remove single quotes
    if( s.size() > 2 && s[0] == '\'' && s[s.size() - 1] == '\'' )
    {
        s.erase( 0, 1 );
        s.erase( s.size() - 1, 1 );
    }
    // remove double quotes
    if( s.size() > 2 && s[0] == '"' && s[s.size() - 1] == '"' )
    {
        s.erase( 0, 1 );
        s.erase( s.size() - 1, 1 );
    }
    return s;
}  // strip_quotes

std::string xml_escape_data(const std::string& src)
{
    std::stringstream dst;
    for (char ch : src) {
        switch (ch) {
            case '&':  dst << "&amp;";  break;
            case '\'': dst << "&apos;"; break;
            case '"':  dst << "&quot;"; break;
            case '<':  dst << "&lt;";   break;
            case '>':  dst << "&gt;";   break;
            default:   dst << ch;       break;
        }
    }
    return dst.str();
}  // xml_escape_data

std::string xml_escape_name(const std::string& src)
{
    std::stringstream dst;
    for (char ch : src) {
        switch (ch) {
            case '{':  dst << "LBC";    break;
            case '}':  dst << "RBC";    break;
            case '[':  dst << "LBK";    break;
            case ']':  dst << "RBK";    break;
            case '(':  dst << "LP";     break;
            case ')':  dst << "RP";     break;
            case '-':  dst << "MINUS";  break;
            case '=':  dst << "ASSIGN"; break;
            default:   dst << ch;       break;
        }
    }
    return dst.str();
}  // xml_escape_name

}
