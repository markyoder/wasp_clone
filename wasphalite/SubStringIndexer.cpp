#include "wasphalite/SubStringIndexer.h"

namespace wasp{

SubStringIndexer::SubStringIndexer()
{

}

SubStringIndexer::SubStringIndexer(const SubStringIndexer &orig)
    : m_indices( orig.m_indices )
{

}


SubStringIndexer::~SubStringIndexer()
{
}

SubStringIndexer::SubStringIndexer(const std::string& str
                                   , const std::string& substr)
{
    index(str, substr);
}

bool SubStringIndexer::index(const std::string& str
                                   , const std::string& substr)
{

    if( str.empty() ) return false;
    if( substr.empty() ) return false;
    size_t index = 0;
    while( (index = str.find(substr, index) ) != std::string::npos )
    {
        m_indices.push_back(index);
        index+= substr.size();
        if( index >= str.size() ) break;
    }
    // indicate we found substrings
    return m_indices.empty() == false;
}
} // end of namespace
