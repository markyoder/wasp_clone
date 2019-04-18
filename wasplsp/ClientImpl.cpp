#include "wasplsp/ClientImpl.h"
#include <unistd.h>

namespace wasp {
namespace lsp  {

bool ClientImpl::connect( std::shared_ptr<Connection> connection )
{
    bool pass = true;

    if ( this->is_connected )
    {
        this->errors << m_error << "Client already connected" << std::endl;

        pass = false;
    }
    else
    {
        this->connection = connection;

        this->is_connected = true;
    }

    return pass;
}

bool ClientImpl::initialize()
{
    if ( !this->is_connected )
    {
        this->errors << m_error << "Client not connected" << std::endl;

        return false;
    }

    if ( this->is_initialized )
    {
        this->errors << m_error << "Connection already initialized" << std::endl;

        return false;
    }

    bool pass = true;

    DataObject client_object;
    DataObject client_capabilities;

    DataObject response_object;
    int        response_request_id;
    DataObject response_capabilities;

    this->incrementRequestID();

    pass &= buildInitializeRequest( client_object       ,
                                    this->errors        ,
                                    this->request_id    ,
                                    0000                ,
                                    "temp-root-uri"     ,
                                    client_capabilities );

    pass &= connection->clientWrite( client_object , this->errors );

    pass &= connection->clientRead( response_object , this->errors );

    pass &= dissectInitializeResponse( response_object     ,
                                       this->errors        ,
                                       response_request_id ,
                                       response_capabilities );

    if ( response_request_id != this->request_id )
    {
        this->errors << m_error << "Initialize response id mismatch" << std::endl;

        pass = false;
    }

    this->is_initialized = true;

    return pass;
}

bool ClientImpl::initialized()
{
    if ( !this->is_connected )
    {
        this->errors << m_error << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error << "Connection not initialized" << std::endl;

        return false;
    }

    bool pass = true;

    DataObject client_object;

    pass &= buildInitializedNotification( client_object ,
                                          this->errors  );

    pass &= connection->clientWrite( client_object , this->errors );

    return pass;
}

bool ClientImpl::opened( const std::string & document_path        ,
                         const std::string & document_language_id ,
                         const std::string & document_text        )
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool ClientImpl::changed( int                 start_line        ,
                          int                 start_character   ,
                          int                 end_line          ,
                          int                 end_character     ,
                          int                 range_length      ,
                          const std::string & new_document_text )
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool ClientImpl::completion( int line      ,
                             int character )
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool ClientImpl::definition( int line      ,
                             int character )
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool ClientImpl::references( int  line                ,
                             int  character           ,
                             bool include_declaration )
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool ClientImpl::formatting( int  start_line      ,
                             int  start_character ,
                             int  end_line        ,
                             int  end_character   ,
                             int  tab_size        ,
                             bool insert_spaces   )
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool ClientImpl::closed()
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool ClientImpl::shutdown()
{
    if ( !this->is_connected )
    {
        this->errors << m_error << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error << "Connection needs to be initialized" << std::endl;

        return false;
    }

    if ( this->is_document_open )
    {
        this->errors << m_error << "Document needs to be closed" << std::endl;

        return false;
    }

    bool pass = true;

    DataObject client_object;

    DataObject response_object;
    int        response_request_id;

    this->incrementRequestID();

    pass &= buildShutdownRequest( client_object    ,
                                  this->errors     ,
                                  this->request_id );

    pass &= connection->clientWrite( client_object , this->errors );

    pass &= connection->clientRead( response_object , this->errors );

    pass &= dissectShutdownResponse( response_object     ,
                                     this->errors        ,
                                     response_request_id );

    if ( response_request_id != this->request_id )
    {
        this->errors << m_error << "Shutdown response id mismatch" << std::endl;

        pass = false;
    }

    this->is_initialized = false;

    return pass;
}

bool ClientImpl::exit()
{
    bool pass = true;

    if ( !this->is_connected )
    {
        this->errors << m_error << "Client not connected" << std::endl;

        return false;
    }

    if ( this->is_initialized )
    {
        this->errors << m_error << "Connection needs to be shutdown" << std::endl;

        return false;
    }

    DataObject client_object;

    pass &= buildExitNotification( client_object ,
                                   this->errors  );

    pass &= connection->clientWrite( client_object , this->errors );

    this->is_connected = false;

    return pass;
}

} // namespace lsp
} // namespace wasp
