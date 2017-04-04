#ifndef WASP_EXPRINTERPRETER_H
#define WASP_EXPRINTERPRETER_H

#include "waspcore/TreeNodePool.h"
#include "waspcore/Interpreter.h"
#include "waspcore/wasp_bug.h"
#include "waspcore/Format.h"
#include "waspexpr/ExprParser.hpp"
#include "waspexpr/ExprContext.h"
#include <cmath>
#include <sstream>
#include <map>

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

private :
     Context m_context;
public:
     Context & context(){return m_context;}
     const Context & context()const{return m_context;}
     Result evaluate(){
         Result r;
         auto root_view = this->root();
         return r.evaluate(root_view,m_context);
     }
};
#include "waspexpr/ExprInterpreter.i.h"

} // end of namespace
#endif
