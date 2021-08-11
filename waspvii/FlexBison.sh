flex -Caf -8 -v VIILexer.lex
sed -i '' 's/#include <FlexLexer.h>/#include \"waspcore\/FlexLexer.h\"/' VIILexer.cpp 
bison --version
bison VIIParser.bison --report=state --report=lookahead --report=solved  -g
sed -i '' 's/class VIIParser/class WASP_PUBLIC VIIParser/' VIIParser.hpp
