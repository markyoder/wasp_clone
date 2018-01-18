/*
 * File:   halite.cpp
 * Author: Robert A. Lefebvre
 *
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include "waspcore/Object.h"
#include "waspjson/JSONInterpreter.h"
#include "wasphalite/HaliteInterpreter.h"
#include "waspcore/version.h"
using namespace std;
using namespace wasp;

template<class S>
bool evaluate_template(HaliteInterpreter<S>& halite, DataObject& object)
{
    DataAccessor data(&object);
    return halite.evaluate(std::cout, data, &std::cerr);
}

/*
 *
 */
int main(int argc, char** argv)
{
    if (argc == 2 &&
        (std::string(argv[1]) == "-v" || std::string(argv[1]) == "--version"))
    {
        std::cout << wasp_version_info::name << " "
                  << wasp_version_info::full_version << std::endl;
        return 0;
    }

    if (argc < 2)
    {
        std::cout << "Usage: " << std::endl;
        std::cout << "\t" << argv[0] << " template [data.json] " << std::endl;
        std::cout << "\ti.e., " << argv[0]
                  << " /path/to/definition.tmpl /path/to/some/data.json "
                  << std::endl;
        std::cout << " Usage : " << argv[0]
                  << " --version\t(print version info)" << std::endl;
        return 1;
    }
    std::string tmpl = argv[1];
    std::string json = "";
    if (argc == 3)
    {
        json = argv[2];
        if (tmpl.size() > 5 && tmpl.substr(tmpl.size() - 5) == ".json")
        {
            std::swap(tmpl, json);
        }
    }
    if (!wasp::expand_template(std::cout, std::cerr, std::cerr, tmpl, json,
                               true, true))
    {
        return -1;
    }
    return 0;
}
