#ifndef WASP_EXPRINTERPRETER_I_H
#define WASP_EXPRINTERPRETER_I_H
template<class S>
ExprInterpreter<S>::ExprInterpreter(std::ostream & err)
    : Interpreter<S>()
{
}
template<class S>
ExprInterpreter<S>::~ExprInterpreter()
{
}
template<class S>
bool ExprInterpreter<S>::parse(std::istream& in
                                        , std::size_t startLine
                                        , std::size_t startColumn)
{
    return Interpreter<S>::template parse_impl<ExprParser>(in
                ,"input"
                ,startLine
                ,startColumn);
}

template<class S>
template<class T>
typename ExprInterpreter<S>::Result &
ExprInterpreter<S>::Result::evaluate( const T & tree_view
                                      , typename ExprInterpreter<S>::Context & context)
{
    // if an ambiguous 'value' node
    // determine operation via the token's type
   size_t type = tree_view.type();
   if( type == wasp::VALUE ) type = tree_view.token_type();

    // TODO - capture OK values from to_type conversions
    // and present the RESULT as an ERROR if OK=false
   switch ( type )
   {
   default:
   case wasp::UNKNOWN:
           m_type = ERROR;
           string() = error_msg(tree_view, "unable to interpret");
           break;
   case wasp::INT:
       m_type = INTEGER;
       m_value.m_int = tree_view.to_int();
       break;
   case wasp::REAL:
       m_type = REAL;
       m_value.m_real = tree_view.to_double();
       break;
   case wasp::QUOTED_STRING:
       m_type = STRING;
       string() = tree_view.to_string();
       break;
   case wasp::PARENTHESIS:
       evaluate(tree_view.child_at(1),context);
       break;
   case wasp::UNARY_MINUS:
       evaluate(tree_view.child_at(1),context);
       unary_minus();
       break;
   case wasp::UNARY_NOT:
       evaluate(tree_view.child_at(1),context);
       unary_not();
       break;
   case wasp::WASP_AND:
   {
       evaluate(tree_view.child_at(0), context);
       Result right_op;
       right_op.evaluate(tree_view.child_at(2),context);
       and_expr(right_op);
       break;
   }
   case wasp::WASP_OR:
   {
       evaluate(tree_view.child_at(0), context);
       Result right_op;
       right_op.evaluate(tree_view.child_at(2),context);
       or_expr(right_op);
       break;
   }
   case wasp::LT:
   {
       // evaluate this result as the left operation
       evaluate(tree_view.child_at(0), context);
       Result right_op;
       right_op.evaluate(tree_view.child_at(2),context);
       less(right_op);
       break;
   }
   case wasp::LTE:
   {
       // evaluate this result as the left operation
       evaluate(tree_view.child_at(0),context);
       Result right_op;
       right_op.evaluate(tree_view.child_at(2),context);
       less_or_equal(right_op);
       break;
   }
   case wasp::GT:
   {
       // evaluate this result as the left operation
       evaluate(tree_view.child_at(0),context);
       Result right_op;
       right_op.evaluate(tree_view.child_at(2),context);
       greater(right_op);
       break;
   }
   case wasp::GTE:
   {
       // evaluate this result as the left operation
       evaluate(tree_view.child_at(0),context);
       Result right_op;
       right_op.evaluate(tree_view.child_at(2),context);
       greater_or_equal(right_op);
       break;
   }
   case wasp::EQ:
   {
       // evaluate this result as the left operation
       evaluate(tree_view.child_at(0),context);
       Result right_op;
       right_op.evaluate(tree_view.child_at(2),context);
       equal(right_op);
       break;
   }
   case wasp::NEQ:
   {
       // evaluate this result as the left operation
       evaluate(tree_view.child_at(0),context);
       Result right_op;
       right_op.evaluate(tree_view.child_at(2),context);
       not_equal(right_op);
       break;
   }
   case wasp::PLUS:
   {
       // evaluate this result as the left operation
       evaluate(tree_view.child_at(0),context);
       Result right_op;
       right_op.evaluate(tree_view.child_at(2),context);
       plus(right_op);
       break;
   }
   case wasp::MINUS:
   {
       // evaluate this result as the left operation
       evaluate(tree_view.child_at(0),context);
       Result right_op;
       right_op.evaluate(tree_view.child_at(2),context);
       minus(right_op);
       break;
   }
   case wasp::MULTIPLY:
   {
       // evaluate this result as the left operation
       evaluate(tree_view.child_at(0),context);
       Result right_op;
       right_op.evaluate(tree_view.child_at(2),context);
       mult(right_op);
       break;
   }
   case wasp::EXPONENT:
   {
       // evaluate this result as the left operation
       evaluate(tree_view.child_at(0),context);
       Result right_op;
       right_op.evaluate(tree_view.child_at(2),context);
       pow(right_op);
       break;
   }
   case wasp::DIVIDE:
   {
       // evaluate this result as the left operation
       evaluate(tree_view.child_at(0),context);
       Result right_op;
       right_op.evaluate(tree_view.child_at(2),context);
       div(right_op);
       break;
   }
   case wasp::STRING:
   {
       std::string name = tree_view.data();
       auto * v = context.variable(name);
       if( v == nullptr )
       {
           m_type = ERROR;
           string() = error_msg(tree_view,"is not a known variable.");

       }else{
           m_type = v->type();
           switch( m_type ){ // switch on current Result's type
               case BOOLEAN:
               m_value.m_bool = v->boolean();
               break;
           case INTEGER:
               m_value.m_int = v->integer();
               break;
           case REAL:
               m_value.m_real = v->real();
               break;
           case STRING:
               string() = v->string();
               break;
           default:
               // not implemented
               break;
           }
       }
       break;
   }
   case wasp::FUNCTION:
   {
       wasp_check(tree_view.child_count() > 0);
       const auto& name_view = tree_view.child_at(0);
       std::string function_name = name_view.data();

       // functions are of the form
       // name '(' [arg1 [',' argn]] ')'
       // we can traverse range [2,c-1]
       std::vector<Result> function_args;
       wasp_check( tree_view.child_count() > 1 );
       bool function_args_error = false;
       for( size_t c = 2, count = tree_view.child_count()-1;
            c < count; ++c)
       {
           const auto & child_view = tree_view.child_at(c);
           if( child_view.is_decorative()
                   || child_view.type() == wasp::WASP_COMMA) continue;
           function_args.push_back(Result());
           function_args.back().evaluate(child_view, context);
           if( function_args.back().is_error() )
           {
               function_args_error = true;
               m_type = ERROR;
               string() = function_args.back().string();
               break;
           }
       }
       // function arguments contain error
       if( function_args_error )
       {
           break;
       }
       Function * function = context.function(function_name);
       wasp_ensure( function );

       auto f_type = function->type();
       m_type = f_type;
       std::stringstream errs;
       bool eval_ok = true;
       if( f_type == INTEGER )
       {
           m_value.m_int = function->integer(function_args,errs,&eval_ok);
       }else if( f_type == REAL )
       {
           m_value.m_real = function->real(function_args,errs,&eval_ok);
       }else if( f_type == STRING )
       {
           string() = function->string(function_args,errs,&eval_ok);
       }else if ( f_type == BOOLEAN )
       {
           m_value.m_bool = function->boolean(function_args,errs,&eval_ok);
       }
       else {
           wasp_not_implemented("unknown function return type evaluation");
       }

       if( eval_ok == false )
       {
           m_type = ERROR;
           string() = error_msg(tree_view, "unable to interpret, "+errs.str());
       }
       break;
   }
   case wasp::KEYED_VALUE:
   {
       std::string variable_name = tree_view.name();
       evaluate(tree_view.child_at(2),context);
       auto * v = context.variable(variable_name);
       bool new_variable = v != nullptr;
       if( new_variable == false ){
           switch( m_type ){ // switch on current Result's type
               case BOOLEAN:
               context.store(variable_name,boolean());
               break;
           case INTEGER:
               context.store(variable_name,integer());
               break;
           case REAL:
               context.store(variable_name,real());
               break;
           case STRING:
               context.store(variable_name,string());
               break;
           default:
               // not implemented
               break;
           }
       } // end of new variable store
       else {
           switch( m_type ){ // switch on current Result's type
               case BOOLEAN:
               v->store(boolean());
               break;
           case INTEGER:
               v->store(integer());
               break;
           case REAL:
               v->store(real());
               break;
           case STRING:
               v->store(string());
               break;
           default:
               // not implemented
               break;
           }
       }
   }
   case wasp::DOCUMENT_ROOT:
       // evaluate all children, storing only last result
       // TODO - implement
       for( size_t i = 0; i < tree_view.child_count(); ++i)
       {
           evaluate(tree_view.child_at(i),context);
       }
       break;
   } // end of switch

   return *this;
}

template<class S>
void ExprInterpreter<S>::Context::clear(){
    for( auto v: m_variables ) delete v.second;
    m_variables.clear();
    for( auto f: m_functions) delete f.second;
    m_functions.clear();
}

template<class S>
typename ExprInterpreter<S>::Context&
ExprInterpreter<S>::Context::add_default_variables()
{
    store("e",2.7182818284590452353602874713527);
    store("pi",3.14159265359);
    return *this;
}



template<class S>
typename ExprInterpreter<S>::Context&
ExprInterpreter<S>::Context::add_default_functions()
{
    wasp_check( function_exists("sin") == false );
    add_function("sin",new FSin() );
    wasp_check( function_exists("asin") == false );
    add_function("asin",new FASin() );
    wasp_check( function_exists("asinh") == false );
    add_function("asinh",new FASinh() );
    wasp_check( function_exists("cos") == false );
    add_function("cos",new FCos() );
    wasp_check( function_exists("acos") == false );
    add_function("acos",new FACos() );
    wasp_check( function_exists("acosh") == false );
    add_function("acosh",new FACosh() );
    wasp_check( function_exists("tan") == false );
    add_function("tan",new FTan() );
    wasp_check( function_exists("atan2") == false );
    add_function("atan2",new FATan2() );
    wasp_check( function_exists("atan") == false );
    add_function("atan",new FATan() );
    wasp_check( function_exists("atanh") == false );
    add_function("atanh",new FATanh() );
    wasp_check( function_exists("sinh") == false );
    add_function("sinh",new FSinh() );
    wasp_check( function_exists("cosh") == false );
    add_function("cosh",new FCosh() );
    wasp_check( function_exists("Tanh") == false );
    add_function("tanh",new FTanh() );

    wasp_check( function_exists("floor") == false );
    add_function("floor",new FFloor() );
    wasp_check( function_exists("ceil") == false );
    add_function("ceil",new FCeil() );
    wasp_check( function_exists("exp") == false );
    add_function("exp",new FExp() );
    wasp_check( function_exists("log") == false );
    add_function("log",new FLog() );
    wasp_check( function_exists("log10") == false );
    add_function("log10",new FLog10() );
    wasp_check( function_exists("sec") == false );
    add_function("sec",new FSec() );
    wasp_check( function_exists("csc") == false );
    add_function("csc",new FCsc() );
    wasp_check( function_exists("cot") == false );
    add_function("cot",new FCot() );
    wasp_check( function_exists("sqrt") == false );
    add_function("sqrt",new FSqrt() );
    wasp_check( function_exists("pow") == false );
    add_function("pow",new FPow() );

    wasp_check( function_exists("deg2rad") == false );
    add_function("deg2rad",new FDeg2Rad() );

    // popular variants
    wasp_check( function_exists("cosec") == false );
    add_function("cosec",new FCsc() );
    wasp_check( function_exists("ln") == false );
    add_function("ln",new FLog() );
    return *this;
}
template<class S>
bool
ExprInterpreter<S>::Context::function_exists(const std::string & name) const
{
    return m_functions.find(name) != m_functions.end();
}

#endif
