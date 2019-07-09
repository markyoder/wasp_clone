# Language Server Protocol

The Language Server Protocol (LSP) package in WASP provides support for most features of the Language Server Protocol version 3.14.

For the details of the official protocol specifications including requests, responses, parameters, error handling, etc., please see [https://microsoft.github.io/language-server-protocol/specification].

For code examples using the WASP LSP features such as the WASP Language Server, LSPInterpreter, LSP Connection Base, Document Symbol Navigator, etc. see the LSP tests in the code repository.

## WASP Language Server

The WASP Language Server class allows all WASP input processing packages to be used as language servers meeting the protocol specifications, so they may be used by any IDE that support the protocol.

| Method                        | Notes                   |
| ----------------------------- | ----------------------------- |
| setup                         | Setup WASP Language Server for specific validation and template based AutoCompletion |
| handleInitializeRequest       | Handle initialize request from a client and send response |
| handleInitializedNotification | Handle initialized notification from a client with no response |
| handleDidOpenNotification     | Parse new document / validate against the schema / send diagnostics back to client |
| handleDidChangeNotification   | Parse changed document / validate against the schema / send diagnostics back to client |
| handleCompletionRequest       | Use the schema's ExistsIn, ValEnums, InputVariants, etc to provide client AutoCompletion |
| handleDefinitionRequest       | Use the schema's ExistsIn rules to provide GoToDefinition support to the client |
| handleReferencesRequest       | References are not yet supported by the WASP Language Server |
| handleFormattingRequest       | Formatting is not yet supported by the WASP Language Server |
| handleSymbolsRequest          | Convert any WASP parse tree to standard LSP hierarchical document symbols |
| handleDidCloseNotification    | Handle document close notification from a client with no response |
| handleShutdownRequest         | Handle shutdown request from a client and send response |
| handleExitNotification        | Handle exit notification from a client cleanly stopping the server with no response |

* NOTE: Currently the WASP Language Server's handling of the document/didChange notification requires that all range values are "-1" and replaces the entire text of the document with the provides changes. Updates over specific line / column ranges are not yet supported by the WASP Language Server.

## LSPInterpreter

The LSPInterpreter is a wrapper on top of the lower level Client LSP calls to communicate with any language server that meets the protocol specifications. However, this wrapper provides an Interpreter interface familiar to WASP users. This means that any standard language server can be used by an LSPInterpreter transparently to interface like all other WASP input processors.

* NOTE: In order to get the familiar WASP Interpreter parse trees from a language server, the language server must support hierarchical document symbols.  The initialize call from the LSPInterpreter to the language server explicitly requests this hierarchical symbol capability.  So, if this feature is supported by the language server, then the conversion into the familiar Interpreter parse tree will be automatic. However LSP document symbols responses do not provide actual values for the symbols in the hierarchy. Therefore, leaf node values may not appear in the Interpreter parse tree, but all line / column information will be present.
