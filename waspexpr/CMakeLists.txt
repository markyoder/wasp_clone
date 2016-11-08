TRIBITS_SUBPACKAGE(expr)


SET(SOURCE
ExprLexer.cpp
ExprParser.cpp
ExprInterpreter.cpp
)

SET(HEADERS
ExprLexer.h
ExprParser.hpp
ExprInterpreter.h
location.hh
position.hh
stack.hh
Expr.lex
Expr.bison
)

#
# Add library
TRIBITS_ADD_LIBRARY(waspexpr
  SOURCES ${SOURCE}
  NOINSTALLHEADERS ${HEADERS}
)

TRIBITS_ADD_EXECUTABLE(exprls
  SOURCES ListExpr.cpp
  NOEXEPREFIX
  NOEXESUFFIX
  INSTALLABLE
)

#
# Add test directory
TRIBITS_ADD_TEST_DIRECTORIES(test)

INSTALL(FILES ${HEADERS} DESTINATION "include/waspexpr/")
TRIBITS_SUBPACKAGE_POSTPROCESS()
