#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "wasp/version.h"
#include "getpot/GetPotInterpreter.h"

using namespace wasp;

int main (int argc, char *argv[])
{
    if( argc == 1 )
    {
        std::cout<<"Workbench Analysis Sequence Processor (GetPot)"
                <<std::endl
                <<argv[0]
                <<" WASP Version : "
            <<wasp::VERSION_MAJOR<<"."
            <<wasp::VERSION_MINOR<<"."
            <<wasp::VERSION_MICRO<<"."<<std::endl;
        std::cout<<" Usage : "<<argv[0]<<" path/to/GetPot/formatted/input"
                <<std::endl;
        return 1;
    }
    for( size_t j = 1; j < argc; ++j)
    {
        std::ifstream input(argv[j]);
        if (input.fail() || input.bad()) {
            std::cout << "Failed to open/read " << argv[j] << std::endl;
            input.close();
            return 1;
        }
        GetPotInterpreter interpreter;
        bool parsed = interpreter.parse(input);
        if( !parsed )
        {
            return -1;
        }
        interpreter.root().paths(std::cout);
    }
    return 0;
}
