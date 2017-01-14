#ifndef WASP_UTILS_H
#define WASP_UTILS_H
#include <string>
#include <sstream>
namespace wasp{
    /**
     * @brief strip_quotes removes single or double quotes
     * @param s the string to have the quotes removes from.
     * @return a string with 1 set of single or double quotes removed
     */
    std::string strip_quotes( const std::string & s);  
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
}
#endif
