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
}
