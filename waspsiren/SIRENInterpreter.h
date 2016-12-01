
#ifndef WASP_SIRENINTERPRETER_H
#define WASP_SIRENINTERPRETER_H

#include <string>
#include <fstream>
#include <istream>
#include <ostream>
#include <iostream>
#include <vector>
#include <map>
#include <memory>

#include "waspcore/Interpreter.h"
#include "waspsiren/SIRENResultSet.h"

/** The wasp namespace is used to encapsulate the three parser classes
 * wasp::SIRENParser, wasp::SIRENLexerImpl and wasp::SIRENInterpreter */
namespace wasp {

    class SIRENInterpreter : public Interpreter<default_node_type_size,default_node_index_size
            ,default_token_type_size,default_token_index_type_size
            ,default_file_offset_type_size> {
    public:
        typedef std::shared_ptr<SIRENInterpreter> SharedPtr;
        SIRENInterpreter();
        SIRENInterpreter(std::ostream & err);
        virtual ~SIRENInterpreter();

        /** Invoke the lexer and parser for a stream.
         * @param in        input stream
         * @param sname     stream name for error messages
         * @return          true if successfully parsed
         */
        bool parseStream(std::istream& in,
                const std::string& sname = "selection statement", size_t startLine=1u, size_t startColumn=1u);
        bool parse(std::istream &input, size_t startLine=1u, size_t startColumn=1u);
        /** Invoke the lexer and parser on an input string.
         * @param input     input string
         * @param sname     stream name for error messages
         * @return          true if successfully parsed
         */
        bool parseString(const std::string& input,
                const std::string& sname = "selection statement", size_t startLine=1u, size_t startColumn=1u);

    public: // public variables
        /**
         * @brief lexer - current lexer instance
         */
        class SIRENLexerImpl* m_lexer;

        /**
         * @brief streamName - stream name (file or input stream) used for error messages.
         */
        std::string streamName;

        /**
         * @brief traceLexing - variable available for verbosely debugging lexing logic
         * @note '%debug' must be specified in the '.lex' grammar file
         */
        bool traceLexing;
        /**
         * @brief traceParsing - variable available for verbosely debugging parsing logic
         * @note '%debug' must be specified in the '.bison' grammar file
         */
        bool traceParsing;       


        /**
         * @brief evaluate the processed expression againsted the adapted node
         * @param node the adapted node that fulfills the required interface
         * @param result the result to be populated
         * @return the number of results stored in \result
         * The TAdapter class must fulfill the following interface requirements:
         * const char * TAdapter::name()const - returns the name of the node.
         * size_t TAdapter::child_count()const - returns the number of children.
         * TAdapter TAdapter::parent()const - returns the parent of the node.
         * TAdapter TAdapter::child_at(size_t index)const - returns the child of the node.
         * bool TAdapter::has_parent()const - indicate the node has a parent.
         * std::string TAdapter::data()const - acquires the data of the node.
         */
        template<typename TAdapter>
        size_t evaluate(TAdapter & node, SIRENResultSet<TAdapter> & result)const;

    private:

        /**
         * @brief evaluate a node in a given context
         * @param context the context of the evaluation (any, child, predicated child, etc.)
         * @param node the adapter input node to evaluate
         * @param result the result set to store evaluated results on
         * @param stage the stage for on which matches will be conducted
         * @return the number of evaluations captured in the result set for the given context
         */
        template<typename TAdapter>
        size_t evaluate(const TreeNodeView & context
                        , SIRENResultSet<TAdapter> & result
                        , std::vector<TAdapter> & stage)const;
//        template<typename TAdapter>
//        size_t select_any(TreeNodeView & context
//                        , TAdapter & node
//                        , SIRENResultSet<TAdapter> & result)const;


        /**
         * @brief search_child_name searches the staged node's children for specifically named children
         * @param context the context to search for ( the child's name pattern )
         * @param stage the stage on which to search
         * Loops through each staged node searching its children for specifically named child nodes
         */
        template<typename TAdapter>
        void search_child_name(const TreeNodeView & context, std::vector<TAdapter> & stage)const;
        /**
         * @brief search_conditional_predicated_child searches the staged node's children for specifically named children with grandchild attributes
         * @param context the context to search for ( the child's name pattern )
         * @param stage the stage on which to search
         * Loops through each staged node searching its children for specifically named child nodes
         * that contain some predicated selection criteria. E.g., 'obj[name=fred]' reads select nodes named 'obj'
         * only where the obj node has a child node 'name' with value 'fred'.
         */
        template<typename TAdapter>
        void search_conditional_predicated_child(const TreeNodeView & context
                                                 , std::vector<TAdapter> & stage)const;

    }; // end of SIRENInterpreter class
#include "waspsiren/SIRENInterpreter.i.h"
} // namespace wasp
#endif // WASPSIRENINTERPRETER_H
