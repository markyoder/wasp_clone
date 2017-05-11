/* 
 * File:   jsonlist.cpp
 * Author: Robert A. Lefebvre
 *
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "waspjson/JSONInterpreter.h"
using namespace std;
using namespace wasp;

/*
 * 
 */
int main(int argc, char** argv) {

    if( argc != 2 ){
        std::cout<<"Usage: "<<std::endl;
        std::cout<<"\tJSONList inputFile "<<std::endl;
        std::cout<<"\ti.e., jsonlist /path/to/some/input "<<std::endl;
        return 1;
    }
    JSONInterpreter<TreeNodePool<unsigned int, unsigned int
            ,TokenPool<unsigned int,unsigned int, unsigned int>>> parser;
    bool failed = !parser.parseFile(argv[1]);
    if( failed ){
        std::cout<<"***Error : Parsing of "<<argv[1]<<" failed!"<<std::endl;
        return 1;
    }
    parser.root().paths(std::cout);
    
    return 0;
}


