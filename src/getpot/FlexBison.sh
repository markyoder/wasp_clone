flex GetPot.lex
sed -i '' 's/#include <FlexLexer.h>/#include \"wasp\/Flex\/FlexLexer.h\"/' GetPotLexer.cpp 
bison GetPot.bison --report=state --report=lookahead --report=solved  -g
