flex -Ca -v DDILexer.lex
sed -i '' 's/#include <FlexLexer.h>/#include \"waspcore\/FlexLexer.h\"/' DDILexer.cpp 
bison --version
bison DDIParser.bison --report=state --report=lookahead --report=solved  -g
