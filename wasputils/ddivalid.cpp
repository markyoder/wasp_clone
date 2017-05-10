/* 
 * File:   ddivalid.cpp
 * Author: Robert A. Lefebvre
 *
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "waspddi/DDInterpreter.h"
#include "waspddi/DDINodeView.h"
#include "waspson/SONInterpreter.h"
#include "waspson/SONNodeView.h"
#include"wasphive/HIVE.h"
using namespace std;
using namespace wasp;

/*
 * 
 */
int main(int argc, char** argv) {

    if( argc < 3 ){
        std::cout<<"Usage: "<<std::endl;
        std::cout<<"\tDDIValid schema inputFile(s) "<<std::endl;
        std::cout<<"\ti.e., ddilist /path/to/definition.son /path/to/some/input(s)... "<<std::endl;
        return 1;
    }
    


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
    Definition::SP definition = std::make_shared<Definition>();

    if ( !HIVE::create_definition(definition.get()
                                  , schema_root
                                  , definition_errors
                                  , false) )
    {
        std::cerr<<definition_errors.str()<<std::endl;
        return 1;
    }
    int return_code = 0;
    for( size_t i = 2; i < argc; ++i)
    {
        DDInterpreter<TreeNodePool<unsigned int, unsigned int
                ,TokenPool<unsigned int,unsigned int, unsigned int>>> parser;
        parser.set_definition_store(definition);
        bool failed = !parser.parseFile(argv[i]);
        if( failed ){
            std::cout<<"***Error : Parsing of "<<argv[i]<<" failed!"<<std::endl;
            return 1;
        }
        DDINodeView<decltype(parser.root())> input_root = parser.root();
        SONNodeView<decltype(schema.root())> schema_root = schema.root();
        HIVE validation_engine;
        std::vector<std::string> validation_errors;
        bool valid = validation_engine.validate(schema_root,input_root, validation_errors);
        if( !valid )
        { // TODO - pass xml option if so desired.
            validation_engine.printMessages(valid, validation_errors, false, argv[i],std::cout);
            return_code++;
        }
    }
    return return_code;
}


