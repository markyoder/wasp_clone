#include <string>
#include "wasplsp/LSP.h"
#include "waspcore/Object.h"

template <typename S>
bool TestServer::run( S            & input_stream  ,
                      S            & output_stream ,
                      std::ostream & error_stream  )
{
    bool pass = true;

    while(1)
    {
        DataObject  input_object;
        std::string method_name;
        DataObject  output_object;

        pass &= streamToObject<S>( input_stream ,
                                   input_object ,
                                   error_stream );

        if ( input_object[m_method].is_string() )
        {
            method_name = input_object[m_method].to_string();
        }

        if ( method_name == m_method_initialize )
        {
            pass &= this->handleInitializeRequest( input_object  ,
                                                   output_object ,
                                                   error_stream  );
        }
        else if ( method_name == m_method_initialized )
        {
            pass &= this->handleInitializedNotification( input_object ,
                                                         error_stream );
        }
        else if ( method_name == m_method_didopen )
        {
            pass &= this->handleDidOpenNotification( input_object  ,
                                                     output_object ,
                                                     error_stream  );
        }
        else if ( method_name == m_method_didchange)
        {
            pass &= this->handleDidChangeNotification( input_object  ,
                                                       output_object ,
                                                       error_stream  );
        }
        else if ( method_name == m_method_completion )
        {
            pass &= this->handleCompletionRequest( input_object  ,
                                                   output_object ,
                                                   error_stream  );
        }
        else if ( method_name == m_method_definition )
        {
            pass &= this->handleDefinitionRequest( input_object  ,
                                                   output_object ,
                                                   error_stream  );;
        }
        else if ( method_name == m_method_references )
        {
            pass &= this->handleReferencesRequest( input_object  ,
                                                   output_object ,
                                                   error_stream  );
        }
        else if ( method_name == m_method_rangeformat )
        {
            pass &= this->handleRangeFormattingRequest( input_object  ,
                                                        output_object ,
                                                        error_stream  );
        }
        else if ( method_name == m_method_didclose )
        {
            pass &= this->handleDidCloseNotification( input_object ,
                                                      error_stream );
        }
        else if ( method_name == m_method_shutdown )
        {
            pass &= this->handleShutdownRequest( input_object  ,
                                                 output_object ,
                                                 error_stream  );
        }
        else if ( method_name == m_method_exit )
        {
            pass &= this->handleExitNotification( input_object ,
                                                  error_stream );
        }
        else if ( method_name.empty() )
        {
            pass = false;
            error_stream << m_error << "Message to server has no method name"
                         << std::endl;
        }
        else
        {
            pass = false;
            error_stream << m_error << "Message to server has bad method name: "
                         "\"" << method_name << "\"" << std::endl;
        }

        if ( !pass || method_name == m_method_exit ) break;

        if ( !output_object.empty() )
        {
            pass &= objectToStream<S>( output_object ,
                                       output_stream ,
                                       error_stream  );
        }
    }

    return pass;
}
