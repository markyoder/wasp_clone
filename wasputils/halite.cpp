/* 
 * File:   halite.cpp
 * Author: Robert A. Lefebvre
 *
 */


#include <iostream>
#include <fstream>
#include "waspcore/Object.h"
#include "waspjson/JSONInterpreter.h"
#include "wasphalite/HaliteInterpreter.h"

using namespace std;
using namespace wasp;

template<class S>
bool evaluate_template(HaliteInterpreter<S> & halite, DataObject & object)
{
    DataAccessor data(&object);
    return halite.evaluate(std::cout,data,&std::cerr);
}

/*
 * 
 */
int main(int argc, char** argv) {

    if( argc < 2 ){
        std::cout<<"Usage: "<<std::endl;
        std::cout<<"\thalite template [data.json] "<<std::endl;
        std::cout<<"\ti.e., halite /path/to/definition.tmpl /path/to/some/data.json "<<std::endl;
        return 1;
    }

    HaliteInterpreter<TreeNodePool<unsigned int, unsigned int
            ,TokenPool<unsigned int,unsigned int, unsigned int>>> halite;

    bool tmpl_failed = !halite.parseFile(argv[1]);
    if( tmpl_failed )
    {
        std::cout<<"***Error : Parsing of template "<<argv[1]<<" failed!"<<std::endl;
        return 1;
    }
    if( argc < 3 )
    {
        DataObject o;
        bool emitted = evaluate_template(halite,o);

        if( !emitted )
        {
            return 2;
        }
        return 0;
    }
    halite.root().paths(std::cout);
    JSONInterpreter<TreeNodePool<unsigned int, unsigned int
            ,TokenPool<unsigned int,unsigned int, unsigned int>>> json_data;
    bool json_failed = !json_data.parseFile(argv[2]);
    if( json_failed )
    {
        std::cout<<"***Error : Parsing of data "<<argv[2]<<" failed!"<<std::endl;
        return 3;
    }
    DataObject o;
    if( !json_data.generate_object(o,std::cerr) )
    {
        return 4;
    }
    bool emitted = evaluate_template(halite,o);
    
    if( !emitted )
    {
        return 5;
    }
    return 0;
}


