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
std::string trim(  std::string str, const std::string& char_seq )
{
    // trim trailing char sequences
    size_t endpos = str.find_last_not_of(char_seq);
    if( std::string::npos != endpos )
    {
        str = str.substr( 0, endpos+1 );
    }
    // trim leading char sequences
    size_t startpos = str.find_first_not_of(char_seq);
    if( std::string::npos != startpos )
    {
        str = str.substr( startpos );
    }
    return str;
}
}
