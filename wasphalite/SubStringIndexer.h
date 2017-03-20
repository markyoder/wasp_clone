#ifndef HALITE_SUBSTRING_INDEXER_H
#define HALITE_SUBSTRING_INDEXER_H

#include <vector>
#include <string>
#include <utility>

namespace wasp{

class SubStringIndexer{

public:
    typedef std::vector<size_t> Index_type;
    SubStringIndexer();
    SubStringIndexer(const SubStringIndexer& orig);
    ~SubStringIndexer();

    SubStringIndexer(const std::string& str
                   , const std::string& substr
                   );
    bool index(const std::string & str
               , const std::string& substr);


    /**
     * @brief merge produce a merged set of index pairs
     * @param other the indices to merge with
     * @return a vector of paired indices
     * This uses a simple opening/closing matching algorithm
     * where the indices contained in other are deemed the closing indices
     * Note : Not all indices will be in the resulting merged set, only those
     * that are deemed matching
     */
    std::vector<std::pair<size_t,size_t> > merge(const SubStringIndexer& other) const;

    const Index_type& data()const{return m_indices;}
private:    
    Index_type m_indices;
};

} // wasp
#endif
