#ifndef WASP_OBJECT_H
#define WASP_OBJECT_H

#include <map>
#include <string>
#include <vector>

namespace wasp{


/**
 * @brief The Value class represents values of objects (null, integer, double, string, array, or object)
 */
class Value
{
public:
    enum Type : unsigned char {
        TYPE_NULL
        ,TYPE_BOOLEAN
        ,TYPE_INTEGER
        ,TYPE_DOUBLE
        ,TYPE_STRING
        ,TYPE_ARRAY
        ,TYPE_OBJECT
    };
private:
    bool m_allocated;
    Type m_type;
    union DataUnion
    {
        bool m_bool;
        double m_double;
        int m_int;
        char * m_string;
        class DataArray * m_array;
        class DataObject * m_object;
    }m_data;
public:

    /// null constructor
    Value();
    /// copy constructor
    Value(const Value& orig);
    // boolean
    Value(bool v);
    // integer
    Value(int v);
    // double
    Value(double v);
    // const char *
    Value(const char * v);
    // string
    Value(const std::string & v);

    ~Value();

    Value& operator=(const Value& v);

    Value::Type type()const;

    bool is_null()const{return m_type == TYPE_NULL;}
    bool is_integer()const{return m_type == TYPE_INTEGER;}
    bool is_double()const{return m_type == TYPE_DOUBLE;}
    bool is_number()const{return is_integer() || is_double();}
    bool is_bool()const{return m_type == TYPE_BOOLEAN;}
    bool is_string()const{return m_type == TYPE_STRING;}
    bool is_array()const{return m_type == TYPE_ARRAY;}
    bool is_object()const{return m_type == TYPE_OBJECT;}

    bool convertable(Value::Type to)const;

    int to_int()const;
    double to_double()const;
    bool to_bool()const;
    const char * to_cstring()const;
    std::string to_string()const;
    DataArray* to_array()const;
    DataObject* to_object()const;

private:
    /**
     * @brief nullify deletes and nullifies this object
     */
    void nullify();

    /**
     * @brief copy_from copies the given value to this value
     * @param orig the value from which data will be copied
     */
    void copy_from(const Value & orig);
};

class DataArray{
public:
    typedef std::vector<Value> storage_type;
private:
    storage_type m_data;
public:

    DataArray();
    DataArray(const DataArray& orig);
    ~DataArray();

    size_t size()const;
    bool empty()const;

    storage_type::const_iterator begin()const;
    storage_type::const_iterator end()const;
    storage_type::iterator begin();
    storage_type::iterator end();

    Value& operator[](size_t i);

    Value& at(size_t);
    const Value& at(size_t)const;
    void push_back(const Value& n);

};

class DataObject
{
public:
    typedef std::map<std::string, Value> storage_type;

private:
    storage_type m_data;

public:
    DataObject();
    DataObject(const DataObject& orig);
    ~DataObject();

    size_t size()const;
    bool empty()const;

    storage_type::const_iterator find(const std::string & name)const;
    storage_type::iterator find(const std::string & name);

    storage_type::const_iterator begin()const;
    storage_type::const_iterator end()const;

    storage_type::iterator begin();
    storage_type::iterator end();

    Value& operator[](const std::string& name);
    const Value& operator[](const std::string& name)const;

    bool contains(const std::string & name)const;
    std::pair<storage_type::iterator, bool> insert(const std::pair<std::string,Value>&v);

};
} // end of namespace
#endif
