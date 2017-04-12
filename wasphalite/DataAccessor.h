#ifndef HALITE_DATA_ACCESSOR_H
#define HALITE_DATA_ACCESSOR_H

#include "waspcore/Object.h"
#include "waspexpr/ExprContext.h"

namespace wasp{

/**
 * @brief The DataAccessor class is design as the intersection of data, the halite engine, and the expression engine
 */
class DataAccessor : public Context {

public:
    DataAccessor(DataObject * data=nullptr);
    DataAccessor(const DataAccessor& orig);
    virtual ~DataAccessor();

    virtual bool exists(const std::string &name) const;
    virtual Context::Type type(const std::string& name)const;
    virtual bool store(const std::string &name, const bool &v);
    virtual bool store(const std::string &name, const int &v);
    virtual bool store(const std::string &name, const std::string &v);
    virtual bool store(const std::string &name, const double &v);

    virtual bool boolean(const std::string& name,size_t index,bool * ok=nullptr)const;
    virtual bool boolean(const std::string& name,bool * ok=nullptr)const;

    virtual int integer(const std::string& name,size_t index,bool * ok=nullptr)const;
    virtual int integer(const std::string& name,bool * ok=nullptr)const;

    virtual double real(const std::string& name,size_t index,bool * ok=nullptr)const;
    virtual double real(const std::string& name, bool * ok=nullptr)const;

    virtual std::string string(const std::string& name, size_t index,bool * ok=nullptr)const;
    virtual std::string string(const std::string& name,bool * ok=nullptr)const;

    /**
     * @brief object acquire an object with the given name
     * @param name the name of the desired object to acquire
     * @return the object, iff an object with the given name exists, nullptr otherwise
     */
    DataObject * object(const std::string & name)const;

    /**
     * @brief array acquire an array with the given name
     * @param name the name of the desired array to acquire
     * @return the array, iff an array with the given name exists, nullptr otherwise
     */
    DataArray * array(const std::string & name )const;

private:
    /**
     * @brief m_root_data unmanaged data pointer to root of data hierarchy
     */
    DataObject * m_root_data;
    /**
     * @brief m_current_data unmanaged data pointer to current data hierarchy
     */
    DataObject * m_current_data;

};

} // wasp
#endif
