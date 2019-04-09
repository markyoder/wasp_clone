#include "TestServer.h"
#include "wasplsp/Server.h"
#include "wasplsp/LSP.h"
#include "waspcore/Object.h"
#include "gtest/gtest.h"
#include <sstream>
#include <vector>

namespace wasp {
namespace lsp  {
   
TEST(server, handle_initialize)
{
    Server<TestServer> test_server;

    DataObject        initializeRequest;
    std::stringstream errors;

    int               client_request_id =  1;
    int               client_process_id =  12345;
    std::string       client_root_path   = "test/root/uri/string";
    DataObject        client_capabilities;

    ASSERT_TRUE(buildInitializeRequest( initializeRequest   ,
                                        errors              ,
                                        client_request_id   ,
                                        client_process_id   ,
                                        client_root_path    ,
                                        client_capabilities ));


    DataObject initializeResponse;

    ASSERT_TRUE(test_server.handleInitializeRequest( initializeRequest  ,
                                                     initializeResponse ,
                                                     errors             ));

    std::stringstream json;
    initializeResponse.format_json(json);

    std::stringstream json_expected;
    json_expected << R"INPUT({
  "id" : 1
  ,"result" : {
    "capabilities" : {}
  }
})INPUT";

    ASSERT_EQ(json.str() , json_expected.str());
}

TEST(server, handle_initialized)
{
    Server<TestServer> test_server;

    DataObject        initializedNotification;
    std::stringstream errors;

    ASSERT_TRUE(buildInitializedNotification( initializedNotification ,
                                              errors                  ));

    ASSERT_TRUE(test_server.handleInitializedNotification( initializedNotification ,
                                                           errors                  ));
}

TEST(server, handle_shutdown)
{
    Server<TestServer> test_server;

    DataObject        shutdownRequest;
    std::stringstream errors;

    int               client_request_id =  2;

    ASSERT_TRUE(buildShutdownRequest( shutdownRequest   ,
                                      errors            ,
                                      client_request_id ));


    DataObject shutdownResponse;

    ASSERT_TRUE(test_server.handleShutdownRequest( shutdownRequest  ,
                                                   shutdownResponse ,
                                                   errors           ));

    std::stringstream json;
    shutdownResponse.format_json(json);

    std::stringstream json_expected;
    json_expected << R"INPUT({
  "id" : 2
  ,"result" : {}
})INPUT";

    ASSERT_EQ(json.str() , json_expected.str());
}

TEST(server, handle_exit)
{
    Server<TestServer> test_server;

    DataObject        exitNotification;
    std::stringstream errors;

    ASSERT_TRUE(buildExitNotification( exitNotification ,
                                       errors           ));

    ASSERT_TRUE(test_server.handleExitNotification( exitNotification ,
                                                    errors           ));
}

TEST(server, handle_didopen)
{
    Server<TestServer> test_server;

    DataObject        didOpenNotification;
    std::stringstream errors;

    std::string       document_path        = "test/document/uri/string";
    std::string       document_language_id = "test_language_id_string";
    int               document_version     =  1;
    std::string       document_text        = "test\ntext\n1\nstring\n";

    ASSERT_TRUE(buildDidOpenNotification( didOpenNotification  ,
                                          errors               ,
                                          document_path        ,
                                          document_language_id ,
                                          document_version     ,
                                          document_text        ));


    DataObject publishDiagnosticsNotification;

    ASSERT_TRUE(test_server.handleDidOpenNotification( didOpenNotification ,
                                                       publishDiagnosticsNotification ,
                                                       errors                         ));

    std::stringstream json;
    publishDiagnosticsNotification.format_json(json);

    std::stringstream json_expected;
    json_expected << R"INPUT({
  "method" : "textDocument/publishDiagnostics"
  ,"params" : {
    "diagnostics" : [
    {
    "code" : "test.code.11"
    ,"message" : "Test message 11."
    ,"range" : {
      "end" : {
      "character" : 27
      ,"line" : 20
    }
      ,"start" : {
        "character" : 16
        ,"line" : 20
      }
    }
    ,"severity" : 1
    ,"source" : "test_source_11"
  }
    ,{
    "code" : "test.code.22"
    ,"message" : "Test message 22."
    ,"range" : {
      "end" : {
      "character" : 27
      ,"line" : 34
    }
      ,"start" : {
        "character" : 56
        ,"line" : 28
      }
    }
    ,"severity" : 2
    ,"source" : "test_source_22"
  }
    ,{
    "code" : "test.code.33"
    ,"message" : "Test message 33."
    ,"range" : {
      "end" : {
      "character" : 43
      ,"line" : 47
    }
      ,"start" : {
        "character" : 36
        ,"line" : 47
      }
    }
    ,"severity" : 3
    ,"source" : "test_source_33"
  }
  ]
    ,"uri" : "test/document/uri/string"
  }
})INPUT";

    ASSERT_EQ(json.str() , json_expected.str());
}

TEST(server, handle_didchange)
{
    Server<TestServer> test_server;

    DataObject        didChangeNotification;
    std::stringstream errors;

    std::string       document_path    = "test/document/uri/string";
    int               document_version =  2;
    int               start_line       =  0;
    int               start_character  =  0;
    int               end_line         =  3;
    int               end_character    =  7;
    int               range_length     =  0;
    std::string       text             = "test\ntext\n2\nstring\n";

    ASSERT_TRUE(buildDidChangeNotification( didChangeNotification ,
                                            errors                ,
                                            document_path         ,
                                            document_version      ,
                                            start_line            ,
                                            start_character       ,
                                            end_line              ,
                                            end_character         ,
                                            range_length          ,
                                            text                  ));

    DataObject publishDiagnosticsNotification;

    ASSERT_TRUE(test_server.handleDidChangeNotification( didChangeNotification          ,
                                                         publishDiagnosticsNotification ,
                                                         errors                         ));

    std::stringstream json;
    publishDiagnosticsNotification.format_json(json);

    std::stringstream json_expected;
    json_expected << R"INPUT({
  "method" : "textDocument/publishDiagnostics"
  ,"params" : {
    "diagnostics" : [
    {
    "code" : "test.code.44"
    ,"message" : "Test message 44."
    ,"range" : {
      "end" : {
      "character" : 16
      ,"line" : 68
    }
      ,"start" : {
        "character" : 45
        ,"line" : 67
      }
    }
    ,"severity" : 4
    ,"source" : "test_source_44"
  }
    ,{
    "code" : "test.code.55"
    ,"message" : "Test message 55."
    ,"range" : {
      "end" : {
      "character" : 12
      ,"line" : 88
    }
      ,"start" : {
        "character" : 17
        ,"line" : 87
      }
    }
    ,"severity" : 1
    ,"source" : "test_source_55"
  }
  ]
    ,"uri" : "test/document/uri/string"
  }
})INPUT";

    ASSERT_EQ(json.str() , json_expected.str());
}

TEST(server, handle_completion)
{
    Server<TestServer> test_server;

    DataObject        completionRequest;
    std::stringstream errors;

    int               client_request_id =  3;
    std::string       document_path     = "test/document/uri/string";
    int               line              =  4;
    int               character         =  2;

    ASSERT_TRUE(buildCompletionRequest( completionRequest  ,
                                        errors             ,
                                        client_request_id  ,
                                        document_path      ,
                                        line               ,
                                        character          ));  

    DataObject completionResponse;

    ASSERT_TRUE(test_server.handleCompletionRequest( completionRequest  ,
                                                     completionResponse ,
                                                     errors             ));
    std::stringstream json;
    completionResponse.format_json(json);

    std::stringstream json_expected;
    json_expected << R"INPUT({
  "id" : 3
  ,"result" : {
    "isIncomplete" : false
    ,"items" : [
      {
      "deprecated" : false
      ,"detail" : "test type info 1"
      ,"documentation" : "test documentation 1"
      ,"kind" : 1
      ,"label" : "test-label-1"
      ,"preselect" : true
      ,"textEdit" : {
        "newText" : "test-insert-text-1"
        ,"range" : {
          "end" : {
          "character" : 11
          ,"line" : 11
        }
          ,"start" : {
            "character" : 11
            ,"line" : 11
          }
        }
      }
    }
      ,{
      "deprecated" : false
      ,"detail" : "test type info 2"
      ,"documentation" : "test documentation 2"
      ,"kind" : 2
      ,"label" : "test-label-2"
      ,"preselect" : false
      ,"textEdit" : {
        "newText" : "test-insert-text-2"
        ,"range" : {
          "end" : {
          "character" : 22
          ,"line" : 22
        }
          ,"start" : {
            "character" : 22
            ,"line" : 22
          }
        }
      }
    }
      ,{
      "deprecated" : false
      ,"detail" : "test type info 3"
      ,"documentation" : "test documentation 3"
      ,"kind" : 3
      ,"label" : "test-label-3"
      ,"preselect" : false
      ,"textEdit" : {
        "newText" : "test-insert-text-3"
        ,"range" : {
          "end" : {
          "character" : 33
          ,"line" : 33
        }
          ,"start" : {
            "character" : 33
            ,"line" : 33
          }
        }
      }
    }
    ]
  }
})INPUT";

    ASSERT_EQ(json.str() , json_expected.str());
}

TEST(server, handle_definition)
{
    Server<TestServer> test_server;

    DataObject        definitionRequest;
    std::stringstream errors;

    int               client_request_id =  4;
    std::string       document_path     = "test/document/uri/string";
    int               line              =  2;
    int               character         =  5;

    ASSERT_TRUE(buildDefinitionRequest( definitionRequest  ,
                                        errors             ,
                                        client_request_id  ,
                                        document_path      ,
                                        line               ,
                                        character          ));  

    DataObject definitionResponse;

    ASSERT_TRUE(test_server.handleDefinitionRequest( definitionRequest  ,
                                                     definitionResponse ,
                                                     errors             ));
    std::stringstream json;
    definitionResponse.format_json(json);

    std::stringstream json_expected;
    json_expected << R"INPUT({
  "id" : 4
  ,"result" : [
    {
    "range" : {
    "end" : {
    "character" : 11
    ,"line" : 11
  }
    ,"start" : {
      "character" : 11
      ,"line" : 11
    }
  }
    ,"uri" : "test/document/uri/string"
  }
    ,{
    "range" : {
    "end" : {
    "character" : 22
    ,"line" : 22
  }
    ,"start" : {
      "character" : 22
      ,"line" : 22
    }
  }
    ,"uri" : "test/document/uri/string"
  }
    ,{
    "range" : {
    "end" : {
    "character" : 33
    ,"line" : 33
  }
    ,"start" : {
      "character" : 33
      ,"line" : 33
    }
  }
    ,"uri" : "test/document/uri/string"
  }
  ]
})INPUT";

    ASSERT_EQ(json.str() , json_expected.str());
}

} // namespace lsp
} // namespace wasp
