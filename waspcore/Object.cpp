#include "waspcore/Object.h"

#include "waspcore/wasp_bug.h"
#include <string.h> // strdup, free
#include <cstdlib> // atoi/atof, etc

namespace wasp{


Value::Value()
    : m_allocated(false)
    , m_type(TYPE_NULL)
{
}
Value::Value(const Value& orig)
{
    this->copy_from(orig);
}
Value::Value(bool v)
{
    m_data.m_bool = v; m_type = TYPE_BOOLEAN;
}
Value::Value(int v)
{
    m_data.m_int = v; m_type = TYPE_INTEGER;
}
Value::Value(double v)
{
    m_data.m_double = v; m_type = TYPE_DOUBLE;
}
Value::Value(const char * v)
{
    wasp_require(v);
    m_data.m_string = strdup(v); m_type = TYPE_STRING; m_allocated = true;
}
Value::Value(const std::string & v)
{
    m_data.m_string = strdup(v.c_str()); m_type = TYPE_STRING; m_allocated = true;
}
Value::Value(const DataArray & v)
{
    m_data.m_array = new DataArray(v); m_type = TYPE_ARRAY; m_allocated = true;
}
Value::Value(const DataObject & v)
{
    m_data.m_object = new DataObject(v); m_type = TYPE_OBJECT; m_allocated = true;
}
void Value::copy_from(const Value &orig)
{
    m_allocated = orig.m_allocated;
    m_type = orig.m_type;
    switch( m_type )
    {
    case TYPE_NULL:
        break;
    case TYPE_BOOLEAN:
        m_data.m_bool = orig.m_data.m_bool;
        break;
    case TYPE_INTEGER:
        m_data.m_int = orig.m_data.m_int;
        break;
    case TYPE_DOUBLE:
        m_data.m_double = orig.m_data.m_double;
        break;
    case TYPE_STRING:
        wasp_check( m_allocated );
        m_data.m_string = strdup(orig.m_data.m_string);
        break;
    case TYPE_ARRAY:
        wasp_check( m_allocated );
        m_data.m_array = new DataArray(*orig.m_data.m_array);
        wasp_ensure(m_data.m_array);
        break;
    case TYPE_OBJECT:
        wasp_check( m_allocated );
        m_data.m_object = new DataObject(*orig.m_data.m_object);
        wasp_ensure(m_data.m_object);
        break;
    }
}

Value::Type Value::type()const{return m_type;}

Value& Value::operator=(const Value& orig)
{
    // release any allocated memory
    this->nullify();
    // copy form the originator
    this->copy_from(orig);
    return *this;
}
void Value::nullify()
{
    switch( m_type )
    {
    case TYPE_NULL:
        break;
    case TYPE_BOOLEAN:
        break;
    case TYPE_INTEGER:
        break;
    case TYPE_DOUBLE:
        break;
    case TYPE_STRING:
        wasp_check( m_allocated );
        free(m_data.m_string);
        break;
    case TYPE_ARRAY:
        wasp_check( m_allocated );
        delete m_data.m_array;
        break;
    case TYPE_OBJECT:
        wasp_check( m_allocated );
        delete m_data.m_object;
        break;
    }
    m_type = TYPE_NULL;
}

Value::~Value()
{
    this->nullify();
}

int Value::to_int()const
{
    switch( m_type )
    {
    case TYPE_NULL:
        return 0;

    case TYPE_BOOLEAN:
        return int(m_data.m_bool);

    case TYPE_INTEGER:
        return m_data.m_int;

    case TYPE_DOUBLE:
        return int(m_data.m_double);

    case TYPE_STRING:
        wasp_ensure(m_allocated);
        wasp_ensure(m_data.m_string);
        return atoi(m_data.m_string);

    case TYPE_ARRAY:
        wasp_not_implemented("conversion of array to integer");

    case TYPE_OBJECT:
        wasp_not_implemented("conversion of object to integer");
    }
    wasp_not_implemented("unknown type conversion to integer");
}
double Value::to_double()const
{
    switch( m_type )
    {
    case TYPE_NULL:
        return 0.0;

    case TYPE_BOOLEAN:
        return double(m_data.m_bool);

    case TYPE_INTEGER:
        return double(m_data.m_int);

    case TYPE_DOUBLE:
        return m_data.m_double;

    case TYPE_STRING:
        wasp_ensure(m_allocated);
        wasp_ensure(m_data.m_string);
        return atof(m_data.m_string);

    case TYPE_ARRAY:
        wasp_not_implemented("conversion of array to double");

    case TYPE_OBJECT:
        wasp_not_implemented("conversion of object to double");
    }
    wasp_not_implemented("unknown type conversion to double");
}
bool Value::to_bool()const
{
    switch( m_type )
    {
    case TYPE_NULL:
        return false;

    case TYPE_BOOLEAN:
        return m_data.m_bool;

    case TYPE_INTEGER:
        return m_data.m_int ? true : false;

    case TYPE_DOUBLE:
        return m_data.m_double  ? true : false;

    case TYPE_STRING:
        wasp_not_implemented("conversion of string to boolean");

    case TYPE_ARRAY:
        wasp_not_implemented("conversion of array to double");

    case TYPE_OBJECT:
        wasp_not_implemented("conversion of object to double");
    }
    wasp_not_implemented("unknown type conversion to bool");
}
const char* Value::to_cstring()const
{
    switch( m_type )
    {
    case TYPE_NULL:
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
    case TYPE_DOUBLE:
        return nullptr;
    case TYPE_STRING:
        wasp_check( m_allocated );
        return m_data.m_string;

    case TYPE_ARRAY:
        wasp_not_implemented("conversion of array to cstring");

    case TYPE_OBJECT:
        wasp_not_implemented("conversion of object to cstring");
    }
    wasp_not_implemented("unknown type conversion to cstring");
}
std::string Value::to_string()const
{
    switch( m_type )
    {
    case TYPE_NULL:
        return "null";
    case TYPE_BOOLEAN:
        return m_data.m_bool ? "true" : "false";
    case TYPE_INTEGER:
        return std::to_string(m_data.m_int);
    case TYPE_DOUBLE:
        return std::to_string(m_data.m_double);
    case TYPE_STRING:
        wasp_check( m_allocated );
        return m_data.m_string;

    case TYPE_ARRAY:
        wasp_not_implemented("conversion of array to string");

    case TYPE_OBJECT:
        wasp_not_implemented("conversion of object to string");
    }
    wasp_not_implemented("unknown type conversion to string");
}

DataArray* Value::to_array()const
{
    wasp_insist(convertable(TYPE_ARRAY)
                ,"Value object must be convertable to an array");
    return m_data.m_array;
}
DataObject* Value::to_object()const
{
    wasp_insist(convertable(TYPE_OBJECT)
                ,"Value object must be convertable to an object");
    return m_data.m_object;
}
bool Value::convertable(Value::Type to) const
{
    switch( to )
    {
    case TYPE_NULL:
        return ( is_number() && to_double() == 0.0 );
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
    case TYPE_DOUBLE:
        return is_bool() || is_null() || is_number();
    case TYPE_STRING:
        return is_string();
    case TYPE_ARRAY:
        return is_array();
    case TYPE_OBJECT:
        return is_object();

    }
    wasp_not_implemented("unknown type conversion");
}

Value& Value::operator [](const std::string & name)
{
    wasp_check( is_object() );
    DataObject* o = to_object();
    return o->operator [](name);
}
Value Value::operator [](const std::string & name)const
{
    wasp_check( is_object() );
    const DataObject* o = to_object();
    return o->operator [](name);
}
Value& Value::operator [](size_t i)
{
    wasp_check( is_array() );
    DataArray* a = to_array();
    return a->operator [](i);
}
Value Value::operator [](size_t i)const
{
    wasp_check( is_array() );
    DataArray* a = to_array();
    return a->operator [](i);
}
bool Value::empty()const
{
    if( is_array() ){
        wasp_check(to_array());
        return to_array()->empty();
    }
    if( is_object() ){
        wasp_check(to_object());
        return to_object()->empty();
    }
    return is_null();
}
size_t Value::size()const
{
    if( is_array() ){
        wasp_check(to_array());
        return to_array()->size();
    }
    if( is_object() ){
        wasp_check(to_object());
        return to_object()->size();
    }
    return 0;
}

bool Value::format_json(std::ostream & out, int indent_level, int level)const
{
    if( is_object() )
    {
        to_object()->format_json(out, indent_level,level);
    }
    else if( is_array() )
    {
        to_array()->format_json(out, indent_level,level);
    }
    else{
        switch( type() ){
        case TYPE_STRING:
            out<<"\""<<to_string()<<"\"";
            break;
        case TYPE_BOOLEAN:
            out<<std::boolalpha<<to_bool();
            break;
        case TYPE_INTEGER:
            out<<to_int();
            break;
        case TYPE_DOUBLE:
            // TODO determine desire precision
            out<<to_double();
            break;
        case TYPE_NULL:
            out<<"null";
            break;
        default:
            wasp_not_implemented("unknown Object value type json emission");
        }
    }
    return out.good();
}

DataArray::DataArray()
{
}
DataArray::~DataArray()
{
}
DataArray::DataArray(const DataArray &orig)
    :m_data(orig.m_data)
{
}
size_t DataArray::size()const
{
    return m_data.size();
}
bool DataArray::empty()const
{
    return m_data.empty();
}
bool DataArray::format_json(std::ostream & out, int indent_level, int level)const
{
    wasp_require( indent_level >= 0 );
    wasp_require( level >= 0 );
    if( empty() ){
        out<<"[]";
        return true;
    }
    out<<"["<<std::endl;
    wasp_tagged_line("aindent = "<<indent_level*(level+1)<<" level "<<level);
    std::string indent = std::string(indent_level*(level+1),' ');
    out<<indent;
    at(0).format_json(out,indent_level,level);
    out<<std::endl;

    for(size_t i = 1, count = size(); i < count; ++i )
    {
        out<<indent<<",";
        if( !at(i).format_json(out,indent_level, level) ) return false;
        out<<std::endl;
    }
    out<<std::string(indent_level*(level),' ')<<"]";
    return out.good();
}
DataObject::DataObject()
{
}
DataObject::DataObject(const DataObject &orig)
    :m_data(orig.m_data)
{
}

DataObject::~DataObject()
{
}
size_t DataObject::size()const
{
    return m_data.size();
}
bool DataObject::empty()const
{
    return m_data.empty();
}

Value& DataObject::operator [](const std::string & name)
{
    auto itr = m_data.find(name);

    if( itr == m_data.end() )
    {
        auto result_pair = m_data.insert(
                    std::make_pair(name,Value())); // create null entry
        return result_pair.first->second;
    }
    return itr->second;
}
Value DataObject::operator [](const std::string & name)const
{
    auto itr = m_data.find(name);

    if( itr == m_data.end() )
    {
        return Value(); // null value
    }
    return itr->second;
}
bool DataObject::format_json(std::ostream & out, int indent_level, int level)const
{
    wasp_require( indent_level >= 0 );
    wasp_check(level >= 0);
    if( empty() ){
        out<<"{}";
        return true;
    }

    out<<"{"<<std::endl;
    wasp_tagged_line("oindent = "<<indent_level*(level+1)<<" level "<<level);
    std::string indent = std::string(indent_level*(level+1),' ');
    out<<indent;
    auto itr = begin();
    out<<"\""<<itr->first<<"\" : ";
    itr->second.format_json(out,indent_level,level);
    out<<std::endl;
    ++itr;
    for( ; itr != end(); ++itr )
    {
        out<<indent<<",";
        out<<"\""<<itr->first<<"\" : ";
        if( !itr->second.format_json(out,indent_level, level+1) ) return false;
        out<<std::endl;
    }

    out<<std::string(indent_level*(level),' ')<<"}";
    return out.good();
}
} // end of namespace wasp
