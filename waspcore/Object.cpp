#include "waspcore/Object.h"

#include "waspcore/wasp_bug.h"
#include <string.h> // strdup

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
        delete m_data.m_string;
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

DataArray::DataArray()
{
}
DataArray::~DataArray()
{
}
DataArray::DataArray(const DataArray &orig)
{
}

DataObject::DataObject()
{
}
DataObject::DataObject(const DataObject &orig)
{
}

DataObject::~DataObject()
{
}
} // end of namespace wasp
