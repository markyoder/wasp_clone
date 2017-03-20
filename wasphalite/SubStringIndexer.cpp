#include "wasphalite/SubStringIndexer.h"
#include <algorithm> // upper_bound

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

SubStringIndexer::IndexPairs_type SubStringIndexer::merge(const SubStringIndexer& o)const
{

    IndexPairs_type pairs;
    if( o.data().empty() ) return pairs;
    if( data().empty() ) return pairs;

    // working copy of the data
    Index_type opening = data();

    const Index_type& closing = o.data();

    for( size_t i : closing )
    {
        // we are looking for the last element that is less than or equal to i
        // or, said another way, the element before the first element that is
        // greater than i. We can use upper_bound to determine first element
        // greater than i, and simple decrement to acquire the
        // last element that is less than or equal to i.
        auto ub = std::upper_bound(opening.begin(), opening.end(), i);
        // gotcha when i is before the start of the list
        if( ub == opening.begin() )
        {
            continue; // skip these
        }
        ub--;
        pairs.push_back(IndexPair_type(*ub,i ) );
        // remove the matched index
        opening.erase(ub);
    }
    // ensure nested pairs come after parent
    std::sort(pairs.begin(),pairs.end());

    return pairs;
}
} // end of namespace
