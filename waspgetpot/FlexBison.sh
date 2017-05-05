flex -Caf -v GetPot.lex
sed -i '' 's/#include <FlexLexer.h>/#include \"waspcore\/FlexLexer.h\"/' GetPotLexer.cpp 
bison --version
bison GetPot.bison --report=state --report=lookahead
#bison GetPot.bison --report=state --report=lookahead --report=solved  -g
