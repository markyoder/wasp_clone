flex -Caf -v SIRENLexer.lex
sed -i '' 's/#include <FlexLexer.h>/#include \"waspcore\/FlexLexer.h\"/' SIRENLexer.cpp 
bison --version
bison SIRENParser.bison --report=state --report=lookahead --report=solved  -g
#mv SIRENParser.hpp SIRENParser.h
#sed -i '' 's/#include "SIRENParser.hpp"/#include \"SIRENParser.h\"/' SIRENParser.cpp 
