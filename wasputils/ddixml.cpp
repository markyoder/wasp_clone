/* 
 * File:   ddilist.cpp
 * Author: raq
 *
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "waspddi/DDInterpreter.h"
#include "waspson/SONInterpreter.h"
#include "waspson/SONNodeView.h"
#include"wasphive/HIVE.h"
using namespace std;
using namespace wasp;

/*
 * 
 */
int main(int argc, char** argv) {

    if( argc != 3 ){
        std::cout<<"Usage: "<<std::endl;
        std::cout<<"\tDDIXml schema inputFile "<<std::endl;
        std::cout<<"\ti.e., ddixml /path/to/definition.son /path/to/some/input "<<std::endl;
        return 1;
    }
    
    DDInterpreter<TreeNodePool<unsigned int, unsigned int
            ,TokenPool<unsigned int,unsigned int, unsigned int>>> parser;

    SONInterpreter<TreeNodePool<unsigned int, unsigned int
            ,TokenPool<unsigned int,unsigned int, unsigned int>>> schema;
    bool schema_failed = !schema.parseFile(argv[1]);
    if( schema_failed )
    {
        std::cout<<"***Error : Parsing of "<<argv[1]<<" failed!"<<std::endl;
        return 1;
    }
    // Construct the definition
    SONNodeView<decltype(schema.root())> schema_root = schema.root();
    std::stringstream definition_errors;
    if ( !HIVE::create_definition(parser.definition()
                                  , schema_root
                                  , definition_errors
                                  , false) )
    {
        std::cerr<<definition_errors.str()<<std::endl;
        return 1;
    }
    bool failed = !parser.parseFile(argv[2]);
    if( failed ){
        std::cout<<"***Error : Parsing of "<<argv[2]<<" failed!"<<std::endl;
        return 1;
    }
    wasp::to_xml(parser.root(),std::cout);
    return 0;
}


