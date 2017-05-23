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

    if( !wasp::expand_template(std::cout,std::cerr,std::cerr,argv[1]
                               ,argc == 3 ? argv[2] : "",true,true ))
    {
        return -1;
    }
    return 0;
}


