#include "wasphalite/DataAccessor.h"

namespace wasp{

DataAccessor::DataAccessor()
    : m_data(nullptr)
{

}

DataAccessor::DataAccessor(const DataAccessor &orig)
    : m_data(orig.m_data)
{

}


DataAccessor::~DataAccessor()
{

}

} // end of namespace
