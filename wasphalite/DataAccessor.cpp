#include "wasphalite/DataAccessor.h"

namespace wasp{

DataAccessor::DataAccessor(DataObject*data, DataAccessor * parent)
    : m_parent(parent)
    , m_current_data(data)
{
}

DataAccessor::DataAccessor(const DataAccessor &orig)
    : m_parent(orig.m_parent)
    , m_current_data(orig.m_current_data)
{

}


DataAccessor::~DataAccessor()
{

}

bool DataAccessor::exists(const std::string &name) const
{

    bool current_data_exists = m_current_data != nullptr
            && m_current_data->contains(name);
    bool parent_data_exists = false;
    if( current_data_exists == false
            && !(parent_data_exists = ( m_parent && m_parent->exists(name))))
    {
        return Context::exists(name);
    }
    return current_data_exists
            || parent_data_exists;
}
Context::Type DataAccessor::type(const std::string& name)const
{
    bool current_data_exists = m_current_data != nullptr
            && m_current_data->contains(name);
    bool parent_data_exists = false;
    if( current_data_exists == false
            && !(parent_data_exists = ( m_parent && m_parent->exists(name))))
    {
        return Context::type(name);
    }
    if( current_data_exists )
    {
        wasp_check( m_current_data );
        auto itr = m_current_data->find(name);
        if( itr == m_current_data->end() ) return Context::Type::UNDEFINED;
        const wasp::Value & variable = itr->second;
        if( variable.is_double() ) return Context::Type::REAL;
        if( variable.is_int() ) return Context::Type::INTEGER;
        if( variable.is_bool() ) return Context::Type::BOOLEAN;
        if( variable.is_string() ) return Context::Type::STRING;
        if( variable.is_object() ) return Context::Type::STRING;
    }
    else if ( parent_data_exists )
    {
        wasp_check( m_parent );
        return m_parent->type(name);
    }
    return Context::Type::UNDEFINED;
}
Context::Type DataAccessor::type(const std::string& name, size_t index)const
{
    bool current_data_exists = m_current_data != nullptr
            && m_current_data->contains(name);
    bool parent_data_exists = false;
    if( current_data_exists == false
            && !(parent_data_exists = ( m_parent && m_parent->exists(name))))
    {
        return Context::type(name, index);
    }
    if( current_data_exists )
    {
        wasp_check( m_current_data );
        auto itr = m_current_data->find(name);
        if( itr == m_current_data->end() ) return Context::Type::UNDEFINED;
        const wasp::Value & variable = itr->second;
        if( variable.is_array() )
        {
            auto * array = variable.to_array();
            wasp_check( array );
            if( array->size() <= index )
            {
                return Context::Type::UNDEFINED;
            }
            const wasp::Value & variable = array->at(index);
            if( variable.is_double() ) return Context::Type::REAL;
            if( variable.is_int() ) return Context::Type::INTEGER;
            if( variable.is_bool() ) return Context::Type::BOOLEAN;
            if( variable.is_string() ) return Context::Type::STRING;
            if( variable.is_object() ) return Context::Type::STRING;
            return Context::Type::UNDEFINED;
        }
    }
    else if( parent_data_exists )
    {
        wasp_check( m_parent );
        return m_parent->type(name,index);
    }
    return Context::Type::UNDEFINED;
}
bool DataAccessor::store(const std::string &name, const bool &v)
{
    if( m_current_data == nullptr)
    {
        return Context::store(name,v);
    }
    (*m_current_data)[name] = v;
    return true;
}

bool DataAccessor::store(const std::string &name, const int &v)
{
    if( m_current_data == nullptr)
    {
        return Context::store(name,v);
    }
    (*m_current_data)[name] = v;
    return true;
}

bool DataAccessor::store(const std::string &name, const std::string &v)
{
    if( m_current_data == nullptr)
    {
        return Context::store(name,v);
    }
    (*m_current_data)[name] = v;
    return true;
}

bool DataAccessor::store(const std::string &name, const double &v)
{
    if( m_current_data == nullptr)
    {
        return Context::store(name,v);
    }
    (*m_current_data)[name] = v;
    return true;
}

bool DataAccessor::boolean(const std::string& name,size_t index,bool * ok)const
{
    bool current_data_exists = m_current_data != nullptr
            && m_current_data->contains(name);
    bool parent_data_exists = false;
    if( current_data_exists == false
            && !(parent_data_exists = ( m_parent && m_parent->exists(name))))
    {
        return Context::boolean(name,index,ok);
    }
    if( current_data_exists )
    {
        auto itr = m_current_data->find(name);
        DataArray * array = nullptr;
        if( ok && itr == m_current_data->end() ) *ok = false;
        else if( ok )
        {
            *ok = itr->second.is_array();
            if( *ok )
            {
                array = itr->second.to_array();
                *ok = array->at(index).is_primitive();
                if( *ok == false ) return false;
            }
        }
        if( itr->second.is_array() )
        {
            array = itr->second.to_array();
            return array->at(index).to_bool();
        }
    }
    else if( parent_data_exists ){
        return m_parent->boolean(name,index, ok);
    }
    return std::numeric_limits<bool>::quiet_NaN();
}
bool DataAccessor::boolean(const std::string& name, bool * ok)const
{
    bool current_data_exists = m_current_data != nullptr
            && m_current_data->contains(name);
    bool parent_data_exists = false;
    if( current_data_exists == false
            && !(parent_data_exists = ( m_parent && m_parent->exists(name))))
    {
        return Context::boolean(name,ok);
    }
    if( current_data_exists )
    {
        auto itr = m_current_data->find(name);

        if( ok && itr == m_current_data->end() ) *ok = false;
        else if( ok )
        {
            *ok = itr->second.is_primitive();
        }
        return itr->second.to_bool();
    }else if ( parent_data_exists )
    {
        return m_parent->boolean(name,ok);
    }
    return std::numeric_limits<bool>::quiet_NaN();
}
int DataAccessor::integer(const std::string& name,size_t index,bool * ok)const
{
    bool current_data_exists = m_current_data != nullptr
            && m_current_data->contains(name);
    bool parent_data_exists = false;
    if( current_data_exists == false
            && !(parent_data_exists = ( m_parent && m_parent->exists(name))))
    {
        return Context::integer(name,index,ok);
    }
    if( current_data_exists )
    {
        auto itr = m_current_data->find(name);
        DataArray * array = nullptr;
        if( ok && itr == m_current_data->end() ) *ok = false;
        else if( ok )
        {
            *ok = itr->second.is_array();
            if( *ok )
            {
                array = itr->second.to_array();
                *ok = array->at(index).is_primitive();
                if( *ok == false ) return std::numeric_limits<int>::quiet_NaN();
            }
        }
        if( itr->second.is_array() )
        {
            array = itr->second.to_array();
            return array->at(index).to_int();
        }
    }else if( parent_data_exists )
    {
        return m_parent->integer(name, index, ok );
    }
    return std::numeric_limits<int>::quiet_NaN();
}
int DataAccessor::integer(const std::string& name,bool * ok)const
{
    bool current_data_exists = m_current_data != nullptr
            && m_current_data->contains(name);
    bool parent_data_exists = false;
    if( current_data_exists == false
            && !(parent_data_exists = ( m_parent && m_parent->exists(name))))
    {
        return Context::integer(name,ok);
    }
    if( current_data_exists )
    {
        auto itr = m_current_data->find(name);

        if( ok && itr == m_current_data->end() ) *ok = false;
        else if( ok )
        {
            *ok = itr->second.is_primitive();
        }
        return itr->second.to_int();
    }
    else if( parent_data_exists )
    {
        return m_parent->integer(name,ok);
    }
    return std::numeric_limits<int>::quiet_NaN();
}

double DataAccessor::real(const std::string& name,size_t index,bool * ok)const
{
    bool current_data_exists = m_current_data != nullptr
            && m_current_data->contains(name);
    bool parent_data_exists = false;
    if( current_data_exists == false
            && !(parent_data_exists = ( m_parent && m_parent->exists(name))))
    {
        return Context::real(name,index,ok);
    }
    if( current_data_exists )
    {
        auto itr = m_current_data->find(name);
        DataArray * array = nullptr;
        if( ok && itr == m_current_data->end() ) *ok = false;
        else if( ok )
        {
            *ok = itr->second.is_array();
            if( *ok )
            {
                array = itr->second.to_array();
                *ok = array->at(index).is_primitive();
                if( *ok == false ) return std::numeric_limits<double>::quiet_NaN();
            }
        }
        if( itr->second.is_array() )
        {
            array = itr->second.to_array();
            return array->at(index).to_double();
        }
    }
    else if( parent_data_exists )
    {
        return m_parent->real(name,index,ok);
    }
    return std::numeric_limits<double>::quiet_NaN();
}
double DataAccessor::real(const std::string& name, bool * ok)const
{
    bool current_data_exists = m_current_data != nullptr
            && m_current_data->contains(name);
    bool parent_data_exists = false;
    if( current_data_exists == false
            && !(parent_data_exists = ( m_parent && m_parent->exists(name))))
    {
        return Context::real(name,ok);
    }
    if( current_data_exists )
    {
        auto itr = m_current_data->find(name);

        if( ok && itr == m_current_data->end() ) *ok = false;
        else if( ok )
        {
            *ok = itr->second.is_primitive();
        }
        return itr->second.to_double();
    }
    else if (parent_data_exists)
    {
        return m_parent->real(name,ok);
    }
    return std::numeric_limits<double>::quiet_NaN();
}

std::string DataAccessor::string(const std::string& name, size_t index,bool * ok)const
{
    bool current_data_exists = m_current_data != nullptr
            && m_current_data->contains(name);
    bool parent_data_exists = false;
    if( current_data_exists == false
            && !(parent_data_exists = ( m_parent && m_parent->exists(name))))
    {
        return Context::string(name,index,ok);
    }
    if( current_data_exists )
    {
        auto itr = m_current_data->find(name);
        DataArray * array = nullptr;
        if( ok && itr == m_current_data->end() ) *ok = false;
        else if( ok )
        {
            *ok = itr->second.is_array();
            if( *ok )
            {
                array = itr->second.to_array();
                *ok = array->at(index).is_primitive();
                if( *ok == false ) return "";
            }
        }
        if( itr->second.is_array() )
        {
            array = itr->second.to_array();
            return array->at(index).to_string();
        }
    }
    else if( parent_data_exists )
    {
        return m_parent->string(name, index, ok);
    }
    return "";
}
std::string DataAccessor::string(const std::string& name,bool * ok)const
{
    bool current_data_exists = m_current_data != nullptr
            && m_current_data->contains(name);
    bool parent_data_exists = false;
    if( current_data_exists == false
            && !(parent_data_exists = ( m_parent && m_parent->exists(name))))
    {
        return Context::string(name,ok);
    }
    if( current_data_exists )
    {
        auto itr = m_current_data->find(name);

        if( ok && itr == m_current_data->end() ) *ok = false;
        else if( ok )
        {
            *ok = itr->second.is_primitive() || itr->second.is_object();
        }
        return itr->second.to_string();
    }
    else if( parent_data_exists )
    {
        return m_parent->string(name,ok);
    }
    return "";
}

DataObject * DataAccessor::object(const std::string &name) const
{
    if( m_current_data == nullptr ) return nullptr;
    auto itr = m_current_data->find(name);
    if( itr == m_current_data->end() )
    {
        return nullptr;
    }
    if( itr->second.is_object() )
    {
        return itr->second.to_object();
    }
    return nullptr;
}
DataArray * DataAccessor::array(const std::string &name) const
{
    if( m_current_data == nullptr ) return nullptr;
    auto itr = m_current_data->find(name);
    if( itr == m_current_data->end() )
    {
        return nullptr;
    }
    if( itr->second.is_array() )
    {
        return itr->second.to_array();
    }
    return nullptr;
}
} // end of namespace
