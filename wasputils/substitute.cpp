/*
 * File:   substitute.cpp
 * Author: Robert A. Lefebvre
 *
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include "waspdakota/ParametersFile.h"
#include "waspcore/version.h"
using namespace std;
using namespace wasp;

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
        std::cout << "\t" << argv[0] << " template [dakota_params.in] " << std::endl;
        std::cout << "\ti.e., " << argv[0]
                  << " /path/to/definition.tmpl /path/to/some/dakota_params.in[.#] /path/to/the/results.out[.#] --ldelim \"<\" --rdelim \">\" --hop \".\""
                  << std::endl;
        std::cout << " Usage : " << argv[0]
                  << " --version\t(print version info)" << std::endl
                  << " --ldelim\tset the attribute's left delimiter" << std::endl
                  << " --rdelim\tset the attribute's right delimiter" << std::endl
                  << " --hop\tset the attribute's hierarchical delimiter"<< std::endl;
        return 1;
    }

    std::string tmpl = argv[1];
    std::string params = "";
    std::string results = "";
    std::string ldelim = "<";
    std::string rdelim = ">";
    std::string hop    = ".";

    for ( int i = 1; i < argc; ++i )
    {
        std::string arg = argv[i];
        if (arg.size() > 3 && arg.substr(arg.size() - 3) == ".in")
        {
            params = arg;
        }
        else if (arg.size() > 4 && arg.substr(arg.size() - 4) == ".out")
        {
            results = arg;
        }
        else if (arg.size() > 5 && arg.substr(arg.size() - 5) == ".tmpl")
        {
            tmpl = arg;
        }
        else if (arg == "--ldelim" && i+1 < argc)
        {
            ldelim = argv[i+1];
            i++;
        }
        else if (arg == "--rdelim" && i+1 < argc)
        {
            rdelim = argv[i+1];
            i++;
        }
        else if (arg == "--hop" && i+1 < argc)
        {
            hop = argv[i+1];
            i++;
        }
        // Parameter files can be '*.in.#'
        else if( arg.find(".in.") != std::string::npos)
        {
            params = arg;
        }
        // Result files can be '*.out.#'
        else if( arg.find(".out.") != std::string::npos)
        {
            results = arg;
        }
        else
        {
            std::cerr<<" Unable to determine argument at position "<<i<<" - '"
                    <<arg<<"'"<<std::endl;
            return 1;
        }
    }

    bool success = false;
    if (!results.empty())
    {
        std::ofstream result_stream(results.c_str());
        if (!result_stream.is_open())
        {
            std::cerr<<"***Error: Unable to open '"<<results<<"' for output!"<<std::endl;
            return -2;
        }
        success = wasp::substitute_template(result_stream, std::cerr,
                                            std::cerr, tmpl,
                                            params, true, true,
                                            ldelim, rdelim, hop);
    }
    else
    {

        success = wasp::substitute_template(std::cout, std::cerr,
                                            std::cerr, tmpl,
                                            params, true, true,
                                            ldelim, rdelim, hop);
    }
    if (!success)
    {
        return -1;
    }
    return 0;
}
