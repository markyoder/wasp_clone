# 
# Run from root of repo to format all file (excluding generated parser files)
#
clang-format -style=file -i waspcore/decl.h
clang-format -style=file -i waspcore/Definition.h
clang-format -style=file -i waspcore/FlexLexer.h
clang-format -style=file -i waspcore/Format.h
clang-format -style=file -i waspcore/Interpreter.h
clang-format -style=file -i waspcore/Interpreter.i.h
clang-format -style=file -i waspcore/Object.h
clang-format -style=file -i waspcore/StringPool.h
clang-format -style=file -i waspcore/StringPool.i.h
clang-format -style=file -i waspcore/test/wasp_harness.h
clang-format -style=file -i waspcore/TokenPool.h
clang-format -style=file -i waspcore/TokenPool.i.h
clang-format -style=file -i waspcore/TreeNodePool.h
clang-format -style=file -i waspcore/TreeNodePool.i.h
clang-format -style=file -i waspcore/utils.h
clang-format -style=file -i waspcore/wasp_bug.h
clang-format -style=file -i waspcore/wasp_node.h
clang-format -style=file -i waspddi/DDILexer.h
clang-format -style=file -i waspddi/DDINodeView.h
clang-format -style=file -i waspddi/DDINodeView.i.h
clang-format -style=file -i waspddi/DDInterpreter.h
clang-format -style=file -i waspddi/DDInterpreter.i.h
clang-format -style=file -i waspexpr/ExprContext.h
clang-format -style=file -i waspexpr/ExprInterpreter.h
clang-format -style=file -i waspexpr/ExprInterpreter.i.h
clang-format -style=file -i waspexpr/ExprLexer.h
clang-format -style=file -i waspgetpot/GetPotInterpreter.h
clang-format -style=file -i waspgetpot/GetPotInterpreter.i.h
clang-format -style=file -i waspgetpot/GetPotLexer.h
clang-format -style=file -i waspgetpot/GetPotNodeView.h
clang-format -style=file -i waspgetpot/GetPotNodeView.i.h
clang-format -style=file -i wasphalite/DataAccessor.h
clang-format -style=file -i wasphalite/HaliteInterpreter.h
clang-format -style=file -i wasphalite/HaliteInterpreter.i.h
clang-format -style=file -i wasphalite/HaliteWorkflow.h
clang-format -style=file -i wasphalite/SubStringIndexer.h
clang-format -style=file -i wasphive/AlphaNum.h
clang-format -style=file -i wasphive/HIVE.h
clang-format -style=file -i wasphive/HIVE.i.h
clang-format -style=file -i waspjson/JSONInterpreter.h
clang-format -style=file -i waspjson/JSONInterpreter.i.h
clang-format -style=file -i waspjson/JSONLexer.h
clang-format -style=file -i waspjson/JSONObjectLexer.h
clang-format -style=file -i waspsiren/SIRENInterpreter.h
clang-format -style=file -i waspsiren/SIRENInterpreter.i.h
clang-format -style=file -i waspsiren/SIRENLexer.h
clang-format -style=file -i waspsiren/SIRENResultSet.h
clang-format -style=file -i waspsiren/SIRENResultSet.i.h
clang-format -style=file -i waspson/SONInterpreter.h
clang-format -style=file -i waspson/SONInterpreter.i.h
clang-format -style=file -i waspson/SONLexer.h
clang-format -style=file -i waspson/SONNodeView.h
clang-format -style=file -i waspson/SONNodeView.i.h
clang-format -style=file -i waspcore/Definition.cpp
clang-format -style=file -i waspcore/Interpreter.cpp
clang-format -style=file -i waspcore/Object.cpp
clang-format -style=file -i waspcore/test/tstDefinition.cpp
clang-format -style=file -i waspcore/test/tstFormat.cpp
clang-format -style=file -i waspcore/test/tstObject.cpp
clang-format -style=file -i waspcore/test/tstStringPool.cpp
clang-format -style=file -i waspcore/test/tstTokenPool.cpp
clang-format -style=file -i waspcore/test/tstTreeNodePool.cpp
clang-format -style=file -i waspcore/test/tstTreeNodeView.cpp
clang-format -style=file -i waspcore/test/tstWaspBug.cpp
clang-format -style=file -i waspcore/test/tstWaspUtils.cpp
clang-format -style=file -i waspcore/utils.cpp
clang-format -style=file -i waspddi/test/tstDDI.cpp
clang-format -style=file -i waspexpr/ExprContext.cpp
clang-format -style=file -i waspexpr/ExprInterpreter.cpp
clang-format -style=file -i waspexpr/ListExpr.cpp
clang-format -style=file -i waspexpr/test/tstExpr.cpp
clang-format -style=file -i waspexpr/test/tstExprResults.cpp
clang-format -style=file -i waspgetpot/GetPotInterpreter.cpp
clang-format -style=file -i waspgetpot/test/tstGetPot.cpp
clang-format -style=file -i waspgetpot/test/tstHIVE.cpp
clang-format -style=file -i wasphalite/DataAccessor.cpp
clang-format -style=file -i wasphalite/HaliteWorkflow.cpp
clang-format -style=file -i wasphalite/SubStringIndexer.cpp
clang-format -style=file -i wasphalite/test/tstDataAccessor.cpp
clang-format -style=file -i wasphalite/test/tstHaliteEngine.cpp
clang-format -style=file -i wasphalite/test/tstHaliteErrors.cpp
clang-format -style=file -i wasphalite/test/tstHaliteTreeConstruction.cpp
clang-format -style=file -i wasphalite/test/tstHaliteWorkflow.cpp
clang-format -style=file -i wasphalite/test/tstSubStringIndexer.cpp
clang-format -style=file -i wasphive/HIVE.cpp
clang-format -style=file -i wasphive/test/tstHIVE.cpp
clang-format -style=file -i wasphive/test/tstSON2JSON.cpp
clang-format -style=file -i waspjson/test/tstJSON.cpp
clang-format -style=file -i waspjson/test/tstObjectGeneration.cpp
clang-format -style=file -i waspsiren/SIRENInterpreter.cpp
clang-format -style=file -i waspsiren/test/tstSIRENInterpreter.cpp
clang-format -style=file -i waspsiren/test/tstSIRENParser.cpp
clang-format -style=file -i waspsiren/test/tstSIRENResultSet.cpp
clang-format -style=file -i waspson/test/tstSON.cpp
clang-format -style=file -i wasputils/ddilist.cpp
clang-format -style=file -i wasputils/ddiselect.cpp
clang-format -style=file -i wasputils/ddivalid.cpp
clang-format -style=file -i wasputils/ddixml.cpp
clang-format -style=file -i wasputils/getpotlist.cpp
clang-format -style=file -i wasputils/getpotselect.cpp
clang-format -style=file -i wasputils/getpotvalid.cpp
clang-format -style=file -i wasputils/getpotxml.cpp
clang-format -style=file -i wasputils/halite.cpp
clang-format -style=file -i wasputils/halitelist.cpp
clang-format -style=file -i wasputils/jsonlist.cpp
clang-format -style=file -i wasputils/jsonselect.cpp
clang-format -style=file -i wasputils/jsonxml.cpp
clang-format -style=file -i wasputils/sonjson.cpp
clang-format -style=file -i wasputils/sonlist.cpp
clang-format -style=file -i wasputils/sonschemaskel.cpp
clang-format -style=file -i wasputils/sonselect.cpp
clang-format -style=file -i wasputils/sonvalid.cpp
clang-format -style=file -i wasputils/sonvalidjson.cpp
clang-format -style=file -i wasputils/sonvalidxml.cpp
clang-format -style=file -i wasputils/sonxml.cpp
