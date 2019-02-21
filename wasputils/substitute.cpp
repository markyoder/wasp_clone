/*
 * File:   halite.cpp
 * Author: Robert A. Lefebvre
 *
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include "waspcore/Object.h"
#include "waspdakota/ParametersFile.h"
#include "wasphalite/HaliteInterpreter.h"
#include "waspcore/version.h"
using namespace std;
using namespace wasp;



inline void insert_typed(DataObject::SP& obj_ptr, const std::string& label,
                    const std::string& value)
{
    bool ok = false;

    double d;
    wasp::to_type<double>(d,value, &ok);
    if (ok)
    {
        obj_ptr->insert(std::make_pair(label,d));
        return;
    }
    int i;
    wasp::to_type<int>(i,value, &ok);
    if (ok)
    {
        obj_ptr->insert(std::make_pair(label,i));
        return;
    }

    obj_ptr->insert(std::make_pair(label, value));
}

inline WASP_PUBLIC bool substitute_template(std::ostream&      result,
                                        std::ostream&      elog,
                                        std::ostream&      alog,
                                        const std::string& template_file,
                                        const std::string& parameter_file,
                                        bool               defaultVars,
                                        bool               defaultFuncs,
                                        const std::string& ldelim,
                                        const std::string& rdelim,
                                        const std::string& hop)
{
    HaliteInterpreter<
        TreeNodePool<unsigned int, unsigned int,
                     TokenPool<unsigned int, unsigned int, unsigned int>>>
        halite(elog);
    halite.attr_start_delim() = ldelim;
    halite.attr_end_delim() = rdelim;

    bool tmpl_failed = !halite.parseFile(template_file);
    if (tmpl_failed)
    {
        elog << "***Error : Parsing of template " << template_file << " failed!"
             << std::endl;
        return false;
    }
    // No parameter file, expand template
    if (parameter_file.empty())
    {
        DataObject   o;
        DataAccessor data(&o, nullptr, hop);
        if (defaultVars)
            data.add_default_variables();
        if (defaultFuncs)
            data.add_default_functions();
        bool emitted = halite.evaluate(result, data, &alog);

        if (!emitted)
        {
            return false;
        }
        return true;
    }

    // process param file
    std::ifstream param_file_stream(parameter_file);
    if (!param_file_stream)
    {
        elog << "***Error : Parameter file could not be opened! "
             <<parameter_file<< std::endl;
        return false;
    }
    DataObject::SP obj_ptr = std::make_shared<DataObject>();
    ParametersFile parameters;
    bool           param_failed = !parameters.load(param_file_stream,elog);
    if (param_failed)
    {
        elog << "***Error : failed to load " << parameter_file
             <<"!"<<std::endl;
        return false;
    }

    // add variables to DataObject
    for( size_t i = 0; i < parameters.variable_count(); ++i)
    {
        const auto& label = parameters.variable_label(i);
        const auto& value = parameters.variable_value(i);
        insert_typed(obj_ptr,label, value);
    }
    // add functions to DataObject
    for( size_t i = 0; i < parameters.function_count(); ++i)
    {
        const auto& label = parameters.function_label(i);
        const auto& value = parameters.function_value(i);
        insert_typed(obj_ptr,label, value);
    }
    // add derivative variables
    for( size_t i = 0; i < parameters.derivative_variable_count(); ++i)
    {
        const auto& label = parameters.derivative_variable_label(i);
        const auto& value = parameters.derivative_variable_value(i);
        insert_typed(obj_ptr,label, value);
    }
    // add analysis components
    for( size_t i = 0; i < parameters.analysis_component_count(); ++i)
    {
        const auto& label = parameters.analysis_component_label(i);
        const auto& value = parameters.analysis_component_value(i);
        insert_typed(obj_ptr,label, value);
    }

    DataAccessor data(obj_ptr.get(), nullptr, hop);
    if (defaultVars)
        data.add_default_variables();
    if (defaultFuncs)
        data.add_default_functions();

    bool emitted = halite.evaluate(result, data, &alog);

    if (!emitted)
    {
        return false;
    }
    return true;
} // end of substitute_template

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
                  << " /path/to/definition.tmpl /path/to/some/dakota_params.json --ldelim \"<\" --rdelim \">\" --hop \".\""
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
        else
        {
            std::cerr<<" Unable to determine argument at position "<<i<<" - '"
                    <<arg<<"'"<<std::endl;
            return 1;
        }
    }

    if (!substitute_template(std::cout, std::cerr, std::cerr, tmpl, params,
                               true, true, ldelim, rdelim, hop))
    {
        return -1;
    }
    return 0;
}
