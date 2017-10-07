/*
 * File:   tstHalite.cpp
 * Author: Robert A. Lefebvre
 */

#include <cstdlib>
#include <cstdio> // std::remove(file_name)
#include <sstream>
#include <string>
#include <stdexcept>
#include <functional>
#include "waspcore/Object.h"
#include "wasphalite/HaliteWorkflow.h"

#include "gtest/gtest.h"
using namespace std;
using namespace wasp;

TEST( Halite, Workflow)
{
    {
        std::stringstream template_stream;
        template_stream << R"INPUT(<attribute>)INPUT";
        std::stringstream output_stream;
        DataObject::SP parameters = std::make_shared<DataObject>();
        DataObject& ref = *(parameters.get());
        ref["attribute"] = "value";

        HaliteWorkflow workflow;
        bool template_result = workflow.parseTemplate(template_stream, std::cerr);
        ASSERT_TRUE(template_result);
        bool render_result  = workflow.renderTemplate(parameters, output_stream
                                                      , std::cerr);
        ASSERT_TRUE(render_result);
        ASSERT_EQ(output_stream.str().compare("value"), 0);
    }
    { // test using default variables PI
        std::stringstream template_stream;
        template_stream << R"INPUT(<'attribute'*pi>)INPUT";
        std::stringstream output_stream;
        DataObject::SP parameters = std::make_shared<DataObject>();
        DataObject& ref = *(parameters.get());
        ref["attribute"] = 1.;

        HaliteWorkflow workflow;
        bool template_result = workflow.parseTemplate(template_stream, std::cerr);
        ASSERT_TRUE(template_result);
        workflow.setUseDefaultVariables(true);
        bool render_result  = workflow.renderTemplate(parameters, output_stream
                                                      , std::cerr);
        ASSERT_TRUE(render_result);
        wasp_line("Result '" << output_stream.str() << "'");
        ASSERT_EQ(output_stream.str().compare("3.14159"), 0);
    }
    { // test using default variables E
        std::stringstream template_stream;
        template_stream << R"INPUT(<'attribute'*e>)INPUT";
        std::stringstream output_stream;
        DataObject::SP parameters = std::make_shared<DataObject>();
        DataObject& ref = *(parameters.get());
        ref["attribute"] = 1.;

        HaliteWorkflow workflow;
        bool template_result = workflow.parseTemplate(template_stream, std::cerr);
        ASSERT_TRUE(template_result);
        workflow.setUseDefaultVariables(true);
        bool render_result  = workflow.renderTemplate(parameters, output_stream
                                                      , std::cerr);
        ASSERT_TRUE(render_result);
        wasp_line("Result '" << output_stream.str() << "'");
        ASSERT_EQ(output_stream.str().compare("2.71828"), 0);
    }
    { // test using default function cos(0) is 1
        std::stringstream template_stream;
        template_stream << R"INPUT(<cos('attribute')>)INPUT";
        std::stringstream output_stream;
        DataObject::SP parameters = std::make_shared<DataObject>();
        DataObject& ref = *(parameters.get());
        ref["attribute"] = 0.;

        HaliteWorkflow workflow;
        bool template_result = workflow.parseTemplate(template_stream, std::cerr);
        ASSERT_TRUE(template_result);
        workflow.setUseDefaultFunctions(true);
        bool render_result  = workflow.renderTemplate(parameters, output_stream
                                                      , std::cerr);
        ASSERT_TRUE(render_result);
        wasp_line("Result '" << output_stream.str() << "'");
        ASSERT_EQ(output_stream.str().compare("1"), 0);
    }
}
