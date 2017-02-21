#ifndef WASP_EXPRINTERPRETER_H
#define WASP_EXPRINTERPRETER_H

#include "waspcore/TreeNodePool.h"
#include "waspcore/Interpreter.h"
#include "waspexpr/ExprParser.hpp"
#include <cmath>

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

     class Result{
     public:
         Result():m_type(Type::INTEGER){}
         Result(const Result& orig)
             :m_type(orig.m_type)
         , m_value(orig.m_value)
         , m_string(orig.m_string){

         }
         ~Result(){}

         template<class T>
         Result & evaluate( const T & tree_view)
         {
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
            case wasp::STRING:
            case wasp::QUOTED_STRING:
                m_type = STRING;
                string() = tree_view.to_string();
                break;
            case wasp::PARENTHESIS:
                evaluate(tree_view.child_at(1));
                break;
            case wasp::UNARY_MINUS:
                evaluate(tree_view.child_at(1));
                unary_minus();
                break;
            case wasp::UNARY_NOT:
                evaluate(tree_view.child_at(1));
                unary_not();
                break;
            case wasp::LT:
            {
                // evaluate this result as the left operation
                evaluate(tree_view.child_at(0));
                Result right_op;
                right_op.evaluate(tree_view.child_at(2));
                less(right_op);
                break;
            }
            case wasp::LTE:
            {
                // evaluate this result as the left operation
                evaluate(tree_view.child_at(0));
                Result right_op;
                right_op.evaluate(tree_view.child_at(2));
                less_or_equal(right_op);
                break;
            }
            case wasp::GT:
            {
                // evaluate this result as the left operation
                evaluate(tree_view.child_at(0));
                Result right_op;
                right_op.evaluate(tree_view.child_at(2));
                greater(right_op);
                break;
            }
            case wasp::GTE:
            {
                // evaluate this result as the left operation
                evaluate(tree_view.child_at(0));
                Result right_op;
                right_op.evaluate(tree_view.child_at(2));
                greater_or_equal(right_op);
                break;
            }
            case wasp::PLUS:
            {
                // evaluate this result as the left operation
                evaluate(tree_view.child_at(0));
                Result right_op;
                right_op.evaluate(tree_view.child_at(2));
                plus(right_op);
                break;
            }
            case wasp::MINUS:
            {
                // evaluate this result as the left operation
                evaluate(tree_view.child_at(0));
                Result right_op;
                right_op.evaluate(tree_view.child_at(2));
                minus(right_op);
                break;
            }
            case wasp::MULTIPLY:
            {
                // evaluate this result as the left operation
                evaluate(tree_view.child_at(0));
                Result right_op;
                right_op.evaluate(tree_view.child_at(2));
                mult(right_op);
                break;
            }
            case wasp::EXPONENT:
            {
                // evaluate this result as the left operation
                evaluate(tree_view.child_at(0));
                Result right_op;
                right_op.evaluate(tree_view.child_at(2));
                pow(right_op);
                break;
            }
            case wasp::DIVIDE:
            {
                // evaluate this result as the left operation
                evaluate(tree_view.child_at(0));
                Result right_op;
                right_op.evaluate(tree_view.child_at(2));
                div(right_op);
                break;
            }
            case wasp::DOCUMENT_ROOT:
                // evaluate all children, storing only last result
                // TODO - implement
                for( size_t i = 0; i < tree_view.child_count(); ++i)
                {
                    evaluate(tree_view.child_at(i));
                }
                break;
            } // end of switch

            return *this;
         }

         bool not_equal(const Result& a) const{
            return !equal(a);

         }
         bool equal(const Result& a) const{
             if( is_number() && a.is_number() )
             {
                 return number() == a.number();
             }
             if( m_type != a.m_type ) return false;
             return m_value == a.m_value;
         }
         bool less (const Result & a) {

             if( is_number() && a.is_number() )
             {
                 m_value.m_bool = number() < a.number();
                 m_type = BOOLEAN;
                 return m_value.m_bool;
             }
             if( is_string() && a.is_string() )
             {
                 m_value.m_bool = string() < a.string();
                 m_type = BOOLEAN;
                 return m_value.m_bool;
             }

             return false;
         }
         bool less_or_equal(const Result & a)
         {
             if( is_number() && a.is_number() )
             {
                 m_value.m_bool = number() <= a.number();
                 m_type = BOOLEAN;
                 return m_value.m_bool;
             }
             if( is_string() && a.is_string() )
             {
                 m_type = BOOLEAN;
                 m_value.m_bool = string() <= a.string();
                 return m_value.m_bool;
             }
             return false;
         }
         bool greater (const Result & a) {
             if( is_number() && a.is_number() )
             {
                 m_value.m_bool = number() > a.number();
                 m_type = BOOLEAN;
                 return m_value.m_bool;
             }
             if( is_string() && a.is_string() )
             {
                 m_value.m_bool = string() > a.string();
                 m_type = BOOLEAN;
                 return m_value.m_bool;
             }
             return false;
         }
         bool greater_or_equal(const Result & a){
             if( is_number() && a.is_number() )
             {
                 m_value.m_bool = number() >= a.number();
                 m_type = BOOLEAN;
                 return m_value.m_bool;
             }
             if( is_string() && a.is_string() )
             {
                 m_value.m_bool = string() >= a.string();
                 m_type = BOOLEAN;
                 return m_value.m_bool;
             }
             return false;
         }
         Result& pow (const Result & a){

             if( is_integer() )
             {
                 // integer ^ interger
                 if( a.is_integer() ){
                     m_value.m_int
                             = std::pow(integer(),a.integer());
                 }
                 // integer ^ real
                 else if( a.is_real() ){
                     m_type = REAL;
                     m_value.m_real = std::pow(integer(),a.real());
                 }
                 // integer ^ string
                 else if( a.is_string() )
                 {
                     m_type = STRING;
                     string()
                             = std::to_string(integer())
                             + a.string();
                 }
             }
             else if( is_real() )
             {
                 // real ^ integer
                 if( a.is_integer() ){
                     m_value.m_real
                             = std::pow(real(),a.integer());
                 }
                 // real ^ real
                 else if( a.is_real() ){
                     m_value.m_real = std::pow(real(),a.real());
                 }
                 // real ^ string
                 else if( a.is_string() )
                 {
                     m_type = STRING;
                     string()
                             = std::to_string(real())
                             + a.string();
                 }
             }else if( is_string() ){
                 // string ^ integer
                 if( a.is_integer() ){
                     string()
                             += std::to_string(a.integer());
                 }
                 // string ^ real
                 else if( a.is_real() ){
                     string()
                             += std::to_string(a.real());
                 }
                 // string ^ string
                 else if( a.is_string() )
                 {
                    string()
                            += a.string();
                 }
             }
             return *this;
         }

         Result& plus(const Result&a)
         {
             if( is_integer() )
             {
                 // integer + interger
                 if( a.is_integer() ){
                     m_value.m_int += a.integer();
                 }
                 // integer + real
                 else if( a.is_real() ){
                     m_type = REAL;
                     m_value.m_real = integer()+a.real();
                 }
                 // integer + string
                 else if( a.is_string() )
                 {
                     m_type = STRING;
                     string()
                             = std::to_string(integer())
                             + a.string();
                 }
             }
             else if( is_real() )
             {
                 // real + integer
                 if( a.is_integer() ){
                     m_value.m_real += a.integer();
                 }
                 // real + real
                 else if( a.is_real() ){
                     m_value.m_real += a.real();
                 }
                 // real + string
                 else if( a.is_string() )
                 {
                     m_type = STRING;
                     string()
                             = std::to_string(real())
                             + a.string();
                 }
             }else if( is_string() ){
                 // string + integer
                 if( a.is_integer() ){
                     string()
                             += std::to_string(a.integer());
                 }
                 // string + real
                 else if( a.is_real() ){
                     string()
                             += std::to_string(a.real());
                 }
                 // string + string
                 else if( a.is_string() )
                 {
                    string()
                            += a.string();
                 }
             }
             return *this;
         }

         Result& minus(const Result&a)
         {
             if( is_integer() )
             {
                 // integer - interger
                 if( a.is_integer() ){
                     m_value.m_int -= a.integer();
                 }
                 // integer - real
                 else if( a.is_real() ){
                     m_type = REAL;
                     m_value.m_real = integer()-a.real();
                 }
                 // integer - string
                 else if( a.is_string() )
                 {
                     m_type = STRING;
                     string()
                             = std::to_string(integer())
                             + a.string();
                 }
             }
             else if( is_real() )
             {
                 // real - integer
                 if( a.is_integer() ){
                     m_value.m_real -= a.integer();
                 }
                 // real - real
                 else if( a.is_real() ){
                     m_value.m_real -= a.real();
                 }
                 // real - string
                 else if( a.is_string() )
                 {
                     m_type = STRING;
                     string()
                             = std::to_string(real())
                             + a.string();
                 }
             }else if( is_string() ){
                 // string - integer
                 if( a.is_integer() ){
                     string()
                             += std::to_string(a.integer());
                 }
                 // string - real
                 else if( a.is_real() ){
                     string()
                             += std::to_string(a.real());
                 }
                 // string - string
                 else if( a.is_string() )
                 {
                    string()
                            += a.string();
                 }
             }
             return *this;
         }
         Result& div(const Result&a)
         {
             if( is_integer() )
             {
                 // integer / interger
                 if( a.is_integer() ){
                     m_value.m_int /= a.integer();
                 }
                 // integer / real
                 else if( a.is_real() ){
                     m_type = REAL;
                     m_value.m_real = integer()/a.real();
                 }
                 // integer / string
                 else if( a.is_string() )
                 {
                     m_type = STRING;
                     string()
                             = std::to_string(integer())
                             + a.string();
                 }
             }
             else if( is_real() )
             {
                 // real / integer
                 if( a.is_integer() ){
                     m_value.m_real /= a.integer();
                 }
                 // real / real
                 else if( a.is_real() ){
                     m_value.m_real /= a.real();
                 }
                 // real / string
                 else if( a.is_string() )
                 {
                     m_type = STRING;
                     string()
                             = std::to_string(real())
                             + a.string();
                 }
             }else if( is_string() ){
                 // string / integer
                 if( a.is_integer() ){
                     string()
                             += std::to_string(a.integer());
                 }
                 // string / real
                 else if( a.is_real() ){
                     string()
                             += std::to_string(a.real());
                 }
                 // string / string
                 else if( a.is_string() )
                 {
                    string()
                            += a.string();
                 }
             }
             return *this;
         }
         Result& mult(const Result&a)
         {
             if( is_integer() )
             {
                 // integer * interger
                 if( a.is_integer() ){
                     m_value.m_int *= a.integer();
                 }
                 // integer * real
                 else if( a.is_real() ){
                     m_type = REAL;
                     m_value.m_real = integer()*a.real();
                 }
                 // integer * string
                 else if( a.is_string() )
                 {
                     m_type = STRING;
                     string()
                             = std::to_string(integer())
                             + a.string();
                 }
             }
             else if( is_real() )
             {
                 // real * integer
                 if( a.is_integer() ){
                     m_value.m_real *= a.integer();
                 }
                 // real * real
                 else if( a.is_real() ){
                     m_value.m_real *= a.real();
                 }
                 // real * string
                 else if( a.is_string() )
                 {
                     m_type = STRING;
                     string()
                             = std::to_string(real())
                             + a.string();
                 }
             }else if( is_string() ){
                 // string * integer
                 if( a.is_integer() ){
                     string()
                             += std::to_string(a.integer());
                 }
                 // string * real
                 else if( a.is_real() ){
                     string()
                             += std::to_string(a.real());
                 }
                 // string * string
                 else if( a.is_string() )
                 {
                    string()
                            += a.string();
                 }
             }
             return *this;
         }
         Result& unary_not()
         {

             if( is_bool() )
             {
                 m_value.m_bool = !m_value.m_bool;
                 m_type = BOOLEAN;
             }
             else if( is_integer() )
             {
                 m_value.m_bool = !bool(integer());
                 m_type = BOOLEAN;
             }
             else if( is_real() )
             {
                m_value.m_bool = !bool(real());
                m_type = BOOLEAN;
             }
             else if( is_string() )
             {
                string() = "!"+string();
                m_type = STRING;
             }

             return *this;
         }
         Result& unary_minus(){
             if( is_integer() )
             {
                 m_value.m_int = -(integer());
             }
             else if( is_real() )
             {
                m_value.m_real = -(real());
             }
             else if( is_string() )
             {
                string() = "-"+string();
             }
             return *this;
         }

         int integer()const{return m_value.m_int;}
         double real()const{return m_value.m_real;}
         double number()const{
             switch( m_type )
             {
                case INTEGER:
                 return m_value.m_int;
                case REAL:
                 return m_value.m_real;
             }
             return std::numeric_limits<double>::quiet_NaN();
         }
         bool boolean()const{return m_value.m_bool;}
         const std::string& string()const{
             return (m_string);}

         std::string& string(){
             return (m_string);}

         bool is_bool()const{
             return m_type == BOOLEAN;
         }
         bool is_integer()const{
             return m_type == INTEGER;
         }
         bool is_real()const{
             return m_type == REAL;
         }
         bool is_number()const{
             return m_type == INTEGER
                     || m_type == REAL;
         }
         bool is_error()const{
             return m_type == ERROR;
         }
         bool is_string()const{
             return m_type == STRING;
         }
     private:
         // type of the result
         enum Type : unsigned char{
             BOOLEAN
             ,INTEGER
             ,REAL
             ,STRING
             ,ERROR
         }m_type;
         union Value{
             bool m_bool;
             int m_int;
             double m_real;
         }m_value;
         std::string m_string;

         template<class T>
         std::string error_msg( const T & tree_view, const std::string & msg_str)
         {
             std::stringstream msg;
             msg<<"***Error : '"<<tree_view.name()<<"' at line "
               <<tree_view.line()<<" and column "<<tree_view.column()
              <<" - "<<msg_str<<std::endl;
             return msg.str();
         }
     }; // end of Result

public:
     Result evaluate()const{
         Result r;
         auto root_view = this->root();
         return r.evaluate(root_view);
     }
};
#include "waspexpr/ExprInterpreter.i.h"
} // end of namespace

#endif
