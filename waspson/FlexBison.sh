flex -Caf -v SONLexer.lex
sed -i '' 's/#include <FlexLexer.h>/#include \"waspcore\/FlexLexer.h\"/' SONLexer.cpp 
bison --version
bison SONParser.bison --report=state --report=lookahead --report=solved  -g
#mv SONParser.hpp SONParser.h
#sed -i '' 's/#include "SONParser.hpp"/#include \"SONParser.h\"/' SONParser.cpp 
