#ifndef WASP_UTILS_H
#define WASP_UTILS_H
#include "waspcore/wasp_bug.h"
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

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


    /**
     * @brief to_xml walk the given node and emit xml elements into out
     * @param node the node to convert to xml
     * @param out the stream to emit the xml
     * @param emit_decorative indicates whether to emit decorative nodes to xml stream
     * @param space amount of whitespace to prefix to a line
     * TODO - escape special characters
     */
    template<class TAdapter>
    inline void to_xml(const TAdapter& node, std::ostream & out, bool emit_decorative=true, std::string space="")
    {
        bool decorative = node.is_decorative();
        if( decorative && !emit_decorative ) return;
        size_t child_count = node.child_count();
        // print element name and location
        out<<space<<"<"<<node.name();
        // capture location if it is a leaf
        if( child_count == 0 ) out<<" loc=\""<<node.line()<<"."<<node.column()<<"\"";
        if( decorative ) out<<" dec=\""<<std::boolalpha<<decorative<<"\"";
        out<<">";
        if( child_count == 0 ) out<<node.data();
        else out<<std::endl;
        // recurse into each child
        for( size_t i = 0; i < child_count; ++i )
        {
            to_xml(node.child_at(i),out, emit_decorative, space+"  ");
        }

        // close the element
        if( child_count > 0 ) out<<space;
        out<<"</"<<node.name()<<">"<<std::endl;
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

    /**
     * @brief format variadic template function for type safe printf/Java.Format like capability
     * @param out - the output stream to emit the formatted result
     * @param err - the error stream if an error occurs
     * @param s - the format string
     * @param value the argument to print
     * @param args the additional arguments to print
     * NOTE : format(std::cout, "%%4.8f=|%4.8f|",3.14159265)  => "%4.1f=| 3.1|"
     */
    template<typename T>
    bool format(std::ostream& out,std::ostream& err, const char *s, T value)
    {
        int width = out.width();
        int prec  = out.precision();
        static char conversion_types[] = "dfsge";
        while (*s) {
            // are we encountering a possible format statement
            // %[flags][width][.precision]conversion is lexed and parsed where
            //   flags : justification, sign, padding and parenthesis
            //   '-' The result will be left-justified
            //   '+' The result will always include a sign
            //   ' ' The result will include a leading space for positive values
            //   '0' The result will be zero-padded
            //   '(' The result will enclose negative numbers in parentheses
            //   width : [1-9][0-9]* (cannot start with 0)
            bool include_sign = false; // true when '%+...' is specified
            bool include_lead_space_for_positive = false; // true when '% ...' is specified
            bool include_parenthesis_for_negative = false; // true when '%(...' is specified
            wasp_line("s="<<*s);
            if (*s == '%') {
                // Check for escaped formatting '%%'
                const char * sl = s + 1; // string lookahead char
                if ( *sl== '%') {
                    out << *sl; // emit escaped '%'
                    s=sl+1; // move beyond
                    continue;
                }
                while( *sl )
                {
                    wasp_line("sl="<<*sl);
                    // check for flag
                    if( *sl == '-' )
                    {   // %-..., left justified
                        out<<std::left;
                        ++sl;
                    }
                    else if( *sl == '+' )
                    {   // %+..., include plus for positive numbers
                        include_sign = true;
                        ++sl;
                    }
                    else if( *sl == ' ' )
                    {   // include leading space for positive numbers
                        include_lead_space_for_positive = true;
                        ++sl;
                    }
                    else if( *sl == '0' )
                    {   // pad space with zeros
                        out.fill('0');
                        out<<std::internal;
                        ++sl;
                    }
                    else if( *sl == '(')
                    {   // surround negative numbers with parenthesis
                        include_parenthesis_for_negative = true;
                        ++sl;
                    }
                    else if( *sl == '.') // check for %.'precision''conversion'
                    {   // no width, just precision
                        ++sl; // move beyond '.'
                        const char * p = sl; // cache location of the start of the precision
                        // isdigit returns non-zero when character is a digit
                        while( sl && std::isdigit(*sl) )
                        {
                            ++sl; // move forward
                        }
                        // check for '%.conversion'| '%.NULL' - missing precision
                        if( p == sl )
                        {  // if no difference in character pointers, error
                            err<<"missing precision format statement at index "<<(sl-p);
                            return false;
                        }
                        // the precision should be terminated by the type 'conversion'
                        // check that the 'conversion' is supported
                        if( std::strchr(conversion_types,*sl) == nullptr )
                        {
                            err<<"unsupported format conversion type ("<<*sl<<"), must be one of "<<conversion_types;
                            return false;
                        }
                        // capture the precision
                        std::stringstream prec_substr(std::string(p,sl));
                        prec_substr>>prec;
                        wasp_check( !prec_substr.bad() || !prec_substr.fail() );

                    }
                    else if ( std::isdigit(*sl) ) // check for width
                    {
                        const char * w = sl; // cache beginning of width substr
                        ++sl;
                        while( std::isdigit(*sl) )
                        {
                            ++sl;
                        }
                        // capture the precision
                        std::string substr(w,sl);
                        std::stringstream width_substr(substr);
                        width_substr>>width;
                        wasp_check( !width_substr.bad() || !width_substr.fail() );
                    }
                    else if( std::strchr(conversion_types,*sl) != nullptr )
                    {
                        // a format expression has been consumed, emit the value
                        switch( *sl )
                        {
                        case 'e':
                            out<<std::scientific;
                            break;
                        case 'f':
                            out<<std::fixed;
                            break;
                        case 'g':
                        {
                            if( std::is_fundamental<T>::value  == false )
                            {
                                err<<"format argument is not a fundamental type";
                                return false;
                            }
                            int magnitude = std::floor(std::log10(value));
                            if(  magnitude < -4
                                    && prec >= std::abs(magnitude))
                            {
                                out<<std::scientific;
                                --prec;
                            }
                            else if( magnitude <= -4 )
                            {
                                out<<std::fixed;
                                prec +=3;
                            }
                            else
                            {
                                out<<std::fixed;
                                if( prec > 0 ) prec -=magnitude+1;
                            }
                            break;
                        }
                        case 's':
                            // nothing special to see here ... yet
                            break;
                        case 'd':
                            out<<std::fixed;
                            prec = 0; // float -> integer
                            break;
                        }

                        if( include_parenthesis_for_negative
                                && std::is_fundamental<T>::value
                                && value < 0)
                        {
                            width -=3; // account for ()
                            if( width < 0 ) width = 0;
                            out<<std::setw(width)<<std::setprecision(prec);
                            out<<"("<<-value<<")";
                        }
                        else if( include_sign
                                 && std::is_fundamental<T>::value
                                 && value > 0 )
                        {
                            width-=2; // account for '+'
                            if( width < 0 ) width = 0;
                            out<<std::setw(width)<<std::setprecision(prec);
                            out<<'+'<<value;
                        }
                        else {
                            out<<std::setw(width)<<std::setprecision(prec);
                            out<<value;
                        }
                        break; // break from lookahead loop
                    }else{
                        err<<"'"<<*sl<<"' is an unknown format element";
                        return false;
                    }
                }// end of format lookahead loop
                s = sl; // move forward the lookahead amount
                // ensure we concluded on a conversion type
                if( std::strchr(conversion_types,*sl) == nullptr ){
                    err<<"format type conversion is missing";
                    return false;
                }
                ++s;
            }else{
                // emit intermediate characters
                out << *s++;
            }
        } // eo while loop
        return true;
    } // end of fmt
}
#endif
