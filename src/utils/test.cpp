#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "wasp/version.h"
#include "wasp/core/StringPool.h"
int main (int argc, char *argv[])
{
    std::cout<<
            argv[0]<<" Version : "
            <<wasp::VERSION_MAJOR<<"."
            <<wasp::VERSION_MINOR<<"."
            <<wasp::VERSION_MICRO<<"."<<std::endl;
  return 0;
}
