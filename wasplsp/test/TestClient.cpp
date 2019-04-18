#include "TestClient.h"
#include <unistd.h>

namespace wasp {
namespace lsp  {

bool TestClient::setup( std::shared_ptr<Connection> connection )
{
    if ( this->is_setup )
    {
        this->errors << m_error << "Client already setup" << std::endl;
        return false;
    }

    bool pass = true;

    this->connection = connection;

    this->is_initialized = false;

    this->is_document_open = false;

    this->request_id = 0;

    this->is_setup = true;

    return pass;
}

bool TestClient::initialize()
{
    if ( !this->is_setup )
    {
        this->errors << m_error << "Client not setup" << std::endl;
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

    this->request_id++;

    pass &= buildInitializeRequest( client_object       ,
                                    this->errors        ,
                                    this->request_id    ,
                                    0000                ,
                                    "temp-root-uri"     ,
                                    client_capabilities );

    pass &= connection->client_write( client_object , this->errors );

    pass &= connection->client_read( response_object , this->errors );

    pass &= dissectInitializeResponse( response_object     ,
                                       this->errors        ,
                                       response_request_id ,
                                       response_capabilities );

    if ( response_request_id != this->request_id )
    {
        this->errors << m_error << "Initialize response id mismatch" << std::endl;
        return false;
    }

    this->is_initialized = true;

    return pass;
}

bool TestClient::initialized()
{
    if ( !this->is_setup )
    {
        this->errors << m_error << "Client not setup" << std::endl;
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

    pass &= connection->client_write( client_object , this->errors );

    return pass;
}

bool TestClient::opened( const std::string & document_path        ,
                         const std::string & document_language_id ,
                         const std::string & document_text        )
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool TestClient::changed( int                 start_line        ,
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

bool TestClient::completion( int line      ,
                             int character )
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool TestClient::definition( int line      ,
                             int character )
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool TestClient::references( int  line                ,
                             int  character           ,
                             bool include_declaration )
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool TestClient::formatting( int  start_line      ,
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

bool TestClient::closed()
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool TestClient::shutdown()
{
    if ( !this->is_setup )
    {
        this->errors << m_error << "Client not setup" << std::endl;
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

    this->request_id++;

    pass &= buildShutdownRequest( client_object    ,
                                  this->errors     ,
                                  this->request_id );

    pass &= connection->client_write( client_object , this->errors );

    pass &= connection->client_read( response_object , this->errors );

    pass &= dissectShutdownResponse( response_object     ,
                                     this->errors        ,
                                     response_request_id );

    if ( response_request_id != this->request_id )
    {
        this->errors << m_error << "Shutdown response id mismatch" << std::endl;
        return false;
    }

    this->is_initialized = false;

    return pass;
}

bool TestClient::exit()
{
    bool pass = true;

    if ( !this->is_setup )
    {
        this->errors << m_error << "Client not setup" << std::endl;
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

    pass &= connection->client_write( client_object , this->errors );

    this->is_setup = false;

    return pass;
}

} // namespace lsp
} // namespace wasp
