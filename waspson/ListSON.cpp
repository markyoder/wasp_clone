/* 
 * File:   LIstSON.cpp
 * Author: raq
 *
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "SONInterpreter.h"
using namespace std;
using namespace wasp;

/*
 * 
 */
int main(int argc, char** argv) {

    if( argc != 2 ){
        std::cout<<"Usage: "<<std::endl;
        std::cout<<"\tSONViewer inputFile "<<std::endl;
        std::cout<<"\ti.e., SONViewer /path/to/some/input "<<std::endl;
        return 1;
    }
    
    SONInterpreter<TreeNodePool<unsigned int, unsigned int
            ,TokenPool<unsigned int,unsigned int, unsigned int>>> parser;
    bool failed = !parser.parseFile(argv[1]);
    if( failed ){
        std::cout<<"***Error : Parsing of "<<argv[1]<<" failed!"<<std::endl;
        return 1;
    }
    parser.root().paths(std::cout);
    
    return 0;
}


