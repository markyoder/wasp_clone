#include "wasphalite/DataAccessor.h"

namespace wasp{

DataAccessor::DataAccessor(DataObject*data)
    : m_root_data(data)
    , m_current_data(data)
{
}

DataAccessor::DataAccessor(const DataAccessor &orig)
    : m_root_data(orig.m_root_data)
    , m_current_data(orig.m_current_data)
{

}


DataAccessor::~DataAccessor()
{

}

bool DataAccessor::exists(const std::string &name) const
{

    if( m_current_data == nullptr
            || m_current_data->contains(name) == false)
    {
        return Context::exists(name);
    }
    return m_current_data->contains(name);
}
Context::Type DataAccessor::type(const std::string& name)const
{
    if( m_current_data == nullptr
            || m_current_data->contains(name) == false)
    {
        return Context::type(name);
    }
    auto itr = m_current_data->find(name);
    if( itr == m_current_data->end() ) return Context::Type::UNDEFINED;
    const wasp::Value & variable = itr->second;
    if( variable.is_double() ) return Context::Type::REAL;
    if( variable.is_int() ) return Context::Type::INTEGER;
    if( variable.is_bool() ) return Context::Type::BOOLEAN;
    if( variable.is_string() ) return Context::Type::STRING;
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
    if( m_current_data == nullptr)
    {
        return Context::boolean(name,index,ok);
    }
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
    return array->at(index).to_bool();
}
bool DataAccessor::boolean(const std::string& name, bool * ok)const
{
    if( m_current_data == nullptr)
    {
        return Context::boolean(name,ok);
    }
    auto itr = m_current_data->find(name);

    if( ok && itr == m_current_data->end() ) *ok = false;
    else if( ok )
    {
        *ok = itr->second.is_primitive();
    }
    return itr->second.to_bool();
}

int DataAccessor::integer(const std::string& name,size_t index,bool * ok)const
{
    if( m_current_data == nullptr)
    {
        return Context::integer(name,index,ok);
    }
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
    return array->at(index).to_int();
}
int DataAccessor::integer(const std::string& name,bool * ok)const
{
    if( m_current_data == nullptr)
    {
        return Context::boolean(name,ok);
    }
    auto itr = m_current_data->find(name);

    if( ok && itr == m_current_data->end() ) *ok = false;
    else if( ok )
    {
        *ok = itr->second.is_primitive();
    }
    return itr->second.to_int();
}

double DataAccessor::real(const std::string& name,size_t index,bool * ok)const
{
    if( m_current_data == nullptr)
    {
        return Context::real(name,index,ok);
    }
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
    return array->at(index).to_double();
}
double DataAccessor::real(const std::string& name, bool * ok)const
{
    if( m_current_data == nullptr)
    {
        return Context::real(name,ok);
    }
    auto itr = m_current_data->find(name);

    if( ok && itr == m_current_data->end() ) *ok = false;
    else if( ok )
    {
        *ok = itr->second.is_primitive();
    }
    return itr->second.to_double();
}

std::string DataAccessor::string(const std::string& name, size_t index,bool * ok)const
{
    if( m_current_data == nullptr)
    {
        return Context::string(name,index,ok);
    }
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
    return array->at(index).to_string();
}
std::string DataAccessor::string(const std::string& name,bool * ok)const
{
    if( m_current_data == nullptr)
    {
        return Context::string(name,ok);
    }
    auto itr = m_current_data->find(name);

    if( ok && itr == m_current_data->end() ) *ok = false;
    else if( ok )
    {
        *ok = itr->second.is_primitive();
    }
    return itr->second.to_string();
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
