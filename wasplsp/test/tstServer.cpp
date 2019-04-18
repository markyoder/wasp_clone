#include "TestServer.h"
#include "wasplsp/Server.h"
#include "wasplsp/LSP.h"
#include "waspcore/Object.h"
#include "gtest/gtest.h"
#include <sstream>

namespace wasp {
namespace lsp  {

Server<TestServer> test_server;

TEST(server, handle_initialize)
{
    DataObject        initializeRequest;
    std::stringstream errors;

    int               client_request_id =  1;
    int               client_process_id =  12345;
    std::string       client_root_path  = "test/root/uri/string";
    DataObject        client_capabilities;

    ASSERT_TRUE(buildInitializeRequest( initializeRequest   ,
                                        errors              ,
                                        client_request_id   ,
                                        client_process_id   ,
                                        client_root_path    ,
                                        client_capabilities ));


    DataObject initializeResponse;

    ASSERT_TRUE(test_server.handleInitializeRequest( initializeRequest  ,
                                                     initializeResponse ));

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
    DataObject        initializedNotification;
    std::stringstream errors;

    ASSERT_TRUE(buildInitializedNotification( initializedNotification ,
                                              errors                  ));

    ASSERT_TRUE(test_server.handleInitializedNotification( initializedNotification ));
}

TEST(server, handle_didopen)
{
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
                                                       publishDiagnosticsNotification ));

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
                                                         publishDiagnosticsNotification ));

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
    DataObject        completionRequest;
    std::stringstream errors;

    int               client_request_id =  2;
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
                                                     completionResponse ));

    std::stringstream json;
    completionResponse.format_json(json);

    std::stringstream json_expected;
    json_expected << R"INPUT({
  "id" : 2
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
    DataObject        definitionRequest;
    std::stringstream errors;

    int               client_request_id =  3;
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
                                                     definitionResponse ));

    std::stringstream json;
    definitionResponse.format_json(json);

    std::stringstream json_expected;
    json_expected << R"INPUT({
  "id" : 3
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

TEST(server, handle_references)
{
    DataObject        referencesRequest;
    std::stringstream errors;

    int               client_request_id   =  4;
    std::string       document_path       = "test/document/uri/string";
    int               line                =  1;
    int               character           =  3;
    bool              include_declaration = false;

    ASSERT_TRUE(buildReferencesRequest( referencesRequest   ,
                                        errors              ,
                                        client_request_id   ,
                                        document_path       ,
                                        line                ,
                                        character           ,
                                        include_declaration ));

    DataObject referencesResponse;

    ASSERT_TRUE(test_server.handleReferencesRequest( referencesRequest  ,
                                                     referencesResponse ));

    std::stringstream json;
    referencesResponse.format_json(json);

    std::stringstream json_expected;
    json_expected << R"INPUT({
  "id" : 4
  ,"result" : [
    {
    "range" : {
    "end" : {
    "character" : 44
    ,"line" : 44
  }
    ,"start" : {
      "character" : 44
      ,"line" : 44
    }
  }
    ,"uri" : "test/document/uri/string"
  }
    ,{
    "range" : {
    "end" : {
    "character" : 55
    ,"line" : 55
  }
    ,"start" : {
      "character" : 55
      ,"line" : 55
    }
  }
    ,"uri" : "test/document/uri/string"
  }
  ]
})INPUT";

    ASSERT_EQ(json.str() , json_expected.str());
}

TEST(server, handle_rangeformatting)
{
    DataObject        rangeFormattingRequest;
    std::stringstream errors;

    int               client_request_id =  5;
    std::string       document_path     = "test/document/uri/string";
    int               start_line        =  2;
    int               start_character   =  0;
    int               end_line          =  4;
    int               end_character     =  3;
    int               tab_size          =  4;
    bool              insert_spaces     =  true;


    ASSERT_TRUE(buildRangeFormattingRequest( rangeFormattingRequest ,
                                             errors                 ,
                                             client_request_id      ,
                                             document_path          ,
                                             start_line             ,
                                             start_character        ,
                                             end_line               ,
                                             end_character          ,
                                             tab_size               ,
                                             insert_spaces          ));

    DataObject rangeFormattingResponse;

    ASSERT_TRUE(test_server.handleRangeFormattingRequest( rangeFormattingRequest  ,
                                                          rangeFormattingResponse ));

    std::stringstream json;
    rangeFormattingResponse.format_json(json);

    std::stringstream json_expected;
    json_expected << R"INPUT({
  "id" : 5
  ,"result" : [
    {
    "newText" : "test\n  new\n  text\n  format\n  1"
    ,"range" : {
      "end" : {
      "character" : 3
      ,"line" : 14
    }
      ,"start" : {
        "character" : 1
        ,"line" : 10
      }
    }
  }
    ,{
    "newText" : "test\n  new\n  text\n  format\n  2"
    ,"range" : {
      "end" : {
      "character" : 3
      ,"line" : 24
    }
      ,"start" : {
        "character" : 1
        ,"line" : 20
      }
    }
  }
    ,{
    "newText" : "test\n  new\n  text\n  format\n  3"
    ,"range" : {
      "end" : {
      "character" : 3
      ,"line" : 34
    }
      ,"start" : {
        "character" : 1
        ,"line" : 30
      }
    }
  }
  ]
})INPUT";

    ASSERT_EQ(json.str() , json_expected.str());
}

TEST(server, handle_didclose)
{
    DataObject        didCloseNotification;
    std::stringstream errors;

    std::string       document_path = "test/document/uri/string";

    ASSERT_TRUE(buildDidCloseNotification( didCloseNotification   ,
                                           errors                 ,
                                           document_path          ));

    ASSERT_TRUE(test_server.handleDidCloseNotification( didCloseNotification ));
}

TEST(server, handle_shutdown)
{
    DataObject        shutdownRequest;
    std::stringstream errors;

    int               client_request_id =  7;

    ASSERT_TRUE(buildShutdownRequest( shutdownRequest   ,
                                      errors            ,
                                      client_request_id ));


    DataObject shutdownResponse;

    ASSERT_TRUE(test_server.handleShutdownRequest( shutdownRequest  ,
                                                   shutdownResponse ));

    std::stringstream json;
    shutdownResponse.format_json(json);

    std::stringstream json_expected;
    json_expected << R"INPUT({
  "id" : 7
  ,"result" : {}
})INPUT";

    ASSERT_EQ(json.str() , json_expected.str());
}

TEST(server, handle_exit)
{
    DataObject        exitNotification;
    std::stringstream errors;

    ASSERT_TRUE(buildExitNotification( exitNotification ,
                                       errors           ));

    ASSERT_TRUE(test_server.handleExitNotification( exitNotification ));
}

} // namespace lsp
} // namespace wasp
