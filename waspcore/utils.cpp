#include "waspcore/utils.h"

namespace wasp
{
std::string strip_quotes(const std::string& src)
{
    std::string s = src;
    // remove single quotes
    if (s.size() >= 2 && s[0] == '\'' && s[s.size() - 1] == '\'')
    {
        s.erase(0, 1);
        s.erase(s.size() - 1, 1);
        return s;
    }
    // remove double quotes
    if (s.size() >= 2 && s[0] == '"' && s[s.size() - 1] == '"')
    {
        s.erase(0, 1);
        s.erase(s.size() - 1, 1);
    }
    return s;
}  // strip_quotes

std::string trim(std::string str, const std::string& char_seq)
{
    if (str.size() == char_seq.size() && str == char_seq)
        return "";
    // trim trailing char sequences
    size_t endpos = str.find_last_not_of(char_seq);
    if (std::string::npos != endpos)
    {
        str = str.substr(0, endpos + 1);
    }
    // trim leading char sequences
    size_t startpos = str.find_first_not_of(char_seq);
    if (std::string::npos != startpos)
    {
        str = str.substr(startpos);
    }
    return str;
}

std::string dir_name(const std::string& path)
{
    size_t sep_i = path.find_last_of("/\\");
    if (sep_i != std::string::npos)
        return path.substr(0, sep_i);
    return path;
}
std::string json_escape_string(const std::string& src)
{
    std::stringstream dst;
    for (char ch : src)
    {
        switch (ch)
        {
            case '\\':
                dst << "\\";
                break;
            case '"':
                dst << "\\\"";
                break;
            default:
                dst << ch;
                break;
        }
    }
    return dst.str();
}  // json_escape_data

std::string xml_escape_data(const std::string& src)
{
    std::stringstream dst;
    for (char ch : src)
    {
        switch (ch)
        {
            case '&':
                dst << "&amp;";
                break;
            case '\'':
                dst << "&apos;";
                break;
            case '"':
                dst << "&quot;";
                break;
            case '<':
                dst << "&lt;";
                break;
            case '>':
                dst << "&gt;";
                break;
            default:
                dst << ch;
                break;
        }
    }
    return dst.str();
}  // xml_escape_data

std::string xml_escape_name(const std::string& src)
{
    std::stringstream dst;
    if (src.at(0) >= '0' && src.at(0) <= '9')
    {
        dst << "_";
    }
    for (char ch : src)
    {
        switch (ch)
        {
            case '{':
                dst << "LBC";
                break;
            case '}':
                dst << "RBC";
                break;
            case '[':
                dst << "LBK";
                break;
            case ']':
                dst << "RBK";
                break;
            case '(':
                dst << "LP";
                break;
            case ')':
                dst << "RP";
                break;
            case '-':
                dst << "MINUS";
                break;
            case '=':
                dst << "ASSIGN";
                break;
            case ':':
                dst << "COLON";
                break;
            case ',':
                dst << "COMMA";
                break;
            case '/':
                dst << "FWDSLSH";
                break;
            case '\\':
                dst << "BCKSLSH";
                break;
            default:
                dst << ch;
                break;
        }
    }
    return dst.str();
}  // xml_escape_name
}
