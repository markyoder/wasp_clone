#ifndef WASP_DAKOTA_PARAMETERSFILE_H
#define WASP_DAKOTA_PARAMETERSFILE_H

#include "waspcore/decl.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace wasp{

/**
 * @brief The ParametersFile class
 * This is a class that encapsulates the standard Dakota parameter file format
 *
 * This format is composed of 'blocks' of data
 * indicating variables, functions, derived variables, and analysis compnent
 * labels and values, lastly the dakota evaluation identifier
 *
 *  <int> 'variables'
 *  <double> <label_cdv_i> (i=1 to n_cdv)
 *  <int>    <label_ddiv_i> (i=1 to n_ddiv)
 *  <string> <label_ddsv_i> (i=1 to n_ddsv)
 *  <double> <label_ddrv_i> (i=1 to n_ddrv)
 *  <double> <label_cauv_i> (i=1 to n_cauv)
 *  <int>    <label_dauiv_i> (i=1 to n_dauiv)
 *  <string> <label_dausv_i> (i=1 to n_dausv)
 *  <double> <label_daurv_i> (i=1 to n_daurv)
 *  <double> <label_ceuv_i> (i=1 to n_ceuv)
 *  <int>    <label_deuiv_i> (i=1 to n_deuiv)
 *  <string> <label_deusv_i> (i=1 to n_deusv)
 *  <double> <label_deurv_i> (i=1 to n_deurv)
 *  <double> <label_csv_i> (i=1 to n_csv)
 *  <int>    <label_dsiv_i> (i=1 to n_dsiv)
 *  <string> <label_dssv_i> (i=1 to n_dssv)
 *  <double> <label_dsrv_i> (i=1 to n_dsrv)
 *  <int> 'functions'
 *  <int>  'ASV_'<i>':'<label_response_i> (i=1 to m)
 *  <int> 'derived_variables'
 *  <int> 'DVV_'<i>':'<label_cdv_i> (i=1 to p)
 *  <int> 'analysis_components'
 *  <string> 'AC_'<i>':'<analysis_driver_name_i> (i=1 to q)
 *  <string> eval_id
 *
 */
class WASP_PUBLIC ParametersFile
{
public:
    ParametersFile();
    ParametersFile(const ParametersFile& orig);

    /**
     * @brief load the parameter file with the given stream
     * @param input the stream from which to parse
     * @param errors the stream on which errors will be reported
     * @return
     */
    bool load(std::istream& input, std::ostream& errors);

private:

    struct Block{
        Block();
        Block(const Block& orig);
        Block& operator= ( const Block & o)
        {
            count = o.count;
            name = o.name;
            label_values = o.label_values;
            return *this;
        }
        int count;
        std::string name;
        std::vector<std::pair<std::string, std::string>> label_values;
    };

    static bool load_block(Block& b, std::istream& input,
                              std::ostream& error, int& line);

    /**
     * @brief add adds the given label and value to block
     * @param b the block
     * @param label the label
     * @param value the value (in string form)
     */
    static void add(Block& b, const std::string& label,
                    const std::string& value);
    /**
     * @brief remove_prefix removes the lead text including the first ':'
     * @param b the block on which the labels will have their prefix removed
     */
    static void remove_prefix(Block& b);

    Block m_variable;
    Block m_function;
    Block m_derivative_variable;
    Block m_analysis_component;

    std::string m_eval_id;

public:
    size_t variable_count() const { return m_variable.label_values.size();}
    std::string variable_label(size_t i) const;
    std::string variable_value(size_t i) const;

    size_t function_count() const { return m_function.label_values.size();}
    std::string function_label(size_t i) const;
    std::string function_value(size_t i) const;

    size_t derivative_variable_count() const { return m_derivative_variable.label_values.size();}
    std::string derivative_variable_label(size_t i) const;
    std::string derivative_variable_value(size_t i) const;

    size_t analysis_component_count() const { return m_analysis_component.label_values.size();}
    std::string analysis_component_label(size_t i) const;
    std::string analysis_component_value(size_t i) const;

    std::string eval_id() const {return m_eval_id;}


}; // end of ParametersFile
} // end namespace
#endif
