flex -Ca -v JSONLexer.lex
sed -i '' 's/#include <FlexLexer.h>/#include \"waspcore\/FlexLexer.h\"/' JSONLexer.cpp 
bison --version
bison JSONParser.bison --report=state --report=lookahead --report=solved  -g
