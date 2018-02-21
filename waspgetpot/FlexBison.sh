flex -Caf -v GetPot.lex
sed -i '' 's/#include <FlexLexer.h>/#include \"waspcore\/FlexLexer.h\"/' GetPotLexer.cpp 
bison --version
bison GetPot.bison --report=state --report=lookahead
sed -i '' 's/class GetPotParser/class WASP_PUBLIC GetPotParser/' GetPotParser.hpp
#bison GetPot.bison --report=state --report=lookahead --report=solved  -g
