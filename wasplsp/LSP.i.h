#include <string>
#include <iostream>
#include <sstream>
#include "waspcore/Object.h"

template <typename T>
bool objectToStream( DataObject   & object ,
                     T            & stream ,
                     std::ostream & errors )
{
    bool pass = true;

    object[m_rpc_jsonrpc_key] = m_rpc_jsonrpc_val;

    std::stringstream body;

    object.format_json(body);

    std::stringstream full_buffer;

    full_buffer << m_rpc_content_len_key
                << " "
                << body.str().size()
                << m_rpc_separator
                << body.str();

    stream.str( full_buffer.str() );

    wasp_check( !stream.fail() );

    return pass;
}

template <typename T>
bool streamToObject( T            & stream ,
                     DataObject   & object ,
                     std::ostream & errors )
{
    bool pass = true;

    std::stringstream full_buffer( stream.str() );

    std::string content_length_key;

    full_buffer >> content_length_key;

    wasp_check( content_length_key == m_rpc_content_len_key );

    int content_length_val;

    full_buffer >> content_length_val;

    content_length_val+=4;

    char * content_buffer = new char[ content_length_val ];

    full_buffer.read(content_buffer, content_length_val);

    std::istringstream packet(std::string(content_buffer,content_length_val));

    delete[] content_buffer;

    DataObject::SP json_ptr;

    JSONObjectParser generator(json_ptr, packet, errors, nullptr);

    pass &= (generator.parse() == 0);

    wasp_check( json_ptr != nullptr );

    object = *(json_ptr.get());

    wasp_check( object[m_rpc_jsonrpc_key].is_string() );

    wasp_check( object[m_rpc_jsonrpc_key].to_string() == m_rpc_jsonrpc_val );

    return pass;
}
