/* 
 * File:   LIstSON.cpp
 * Author: raq
 *
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "waspson/SONInterpreter.h"
#include "waspson/SONNodeView.h"
using namespace std;
using namespace wasp;

/*
 * 
 */
int main(int argc, char** argv) {

    if( argc != 2 ){
        std::cout<<"Usage: "<<std::endl;
        std::cout<<"\tsonxml inputFile "<<std::endl;
        std::cout<<"\ti.e., sonxml /path/to/some/input "<<std::endl;
        return 1;
    }
    
    SONInterpreter<TreeNodePool<unsigned int, unsigned int
            ,TokenPool<unsigned int,unsigned int, unsigned int>>> parser;
    bool failed = !parser.parseFile(argv[1]);
    if( failed ){
        std::cout<<"***Error : Parsing of "<<argv[1]<<" failed!"<<std::endl;
        return 1;
    }
    SONNodeView<decltype(parser.root())> root = parser.root();
    wasp::to_xml(root,std::cout);
    return 0;
}


