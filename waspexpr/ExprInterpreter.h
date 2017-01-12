#ifndef WASP_EXPRINTERPRETER_H
#define WASP_EXPRINTERPRETER_H

#include "waspcore/TreeNodePool.h"
#include "waspcore/Interpreter.h"
#include "waspexpr/ExprParser.hpp"

namespace wasp{
template<class S = TreeNodePool<> >
class ExprInterpreter : public Interpreter<S>
{
public:
    ExprInterpreter(std::ostream & error_stream=std::cerr);
    ~ExprInterpreter();

    /**
     * @brief parse parser the given input stream
     * @param input the stream of the input data
     * @param startLine the first line of the input stream
     * @param startColumn the first column of the input stream
     * @return true, iff no input processing errors were encountered
     */
     bool parse(std::istream &input
                       , std::size_t m_start_line=1u
                       , std::size_t m_start_column=1u);

public: // variables
};
#include "waspexpr/ExprInterpreter.i.h"
} // end of namespace

#endif
