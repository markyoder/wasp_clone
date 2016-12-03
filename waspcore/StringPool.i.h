#ifndef WASP_STRINGPOOL_I_H
#define WASP_STRINGPOOL_I_H
    template<typename T>
    const char * StringPool<T>::data(T index)const
    {
        std::size_t data_index = m_token_data_indices[index];
        return &m_data[data_index];
    }
    template<typename T>
    void StringPool<T>::push(const char * str)
    {
        std::size_t string_index = m_data.size();
        // capture str data
        for( std::size_t i = 0; str[i] != '\0'; ++i)
        {
            m_data.push_back(str[i]);
        }
        // ensure null terminated
        m_data.push_back('\0');
        // capture index of new string for book keeping
        m_token_data_indices.push_back(static_cast<T>(string_index));
    }
    template<typename T>
    void StringPool<T>::pop()
    {
        if( m_token_data_indices.empty() ) return;
        T index = m_token_data_indices.back();
        m_data.erase(m_data.begin()+index,m_data.end());
        m_token_data_indices.pop_back();
    }
    // default constructor
    template<typename T>
    StringPool<T>::StringPool()
    {
    }
    // copy constuctor
    template<typename T>
    StringPool<T>::StringPool(const StringPool<T>& orig)
        : m_data(orig.m_data)
        , m_token_data_indices(orig.m_token_data_indices)
    {
    }
    // default destructor
    template<typename T>
    StringPool<T>::~StringPool()
    {
    }

#endif
