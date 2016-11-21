#ifndef SIREN_SIRENRESULTSET_H
#define SIREN_SIRENRESULTSET_H
#include <string>
#include <vector>
namespace wasp{

/**
 * @brief class SIRENResultSet contains the evaluated results from a selection
 *
 */
template< typename TAdapter >
class SIRENResultSet{
public:
    typedef std::pair<std::string,std::string> ScalarResult;
    SIRENResultSet();
    SIRENResultSet( const SIRENResultSet & orig );
    ~SIRENResultSet();

    /**
     * @brief result_count indicates the number of results contain in the set
     * @return set count
     */
    size_t result_count()const{return results.size();}
    /**
     * @brief is_adapted determines if the result at the given index is of type \TAdapter
     * @param index
     * @return true, iff the type at the given index is \TAdapter
     */
    bool is_adapted(size_t index)const{return results[index].first == ADAPTED;}
    /**
     * @brief is_scalar determine if the result at the given index is a named result (count,"3")
     * @param index
     * @return true, iff the type at the given index is a computed result
     */
    bool is_scalar(size_t index)const{return results[index].first == SCALAR;}

    const TAdapter& adapted(size_t index)const{return adapted_results[results[index].second];}
    const ScalarResult& scalar(size_t index)const {return scalar_results[results[index].second];}

    void push( const TAdapter & node );
    void push( const std::string& name, const std::string & data );
private:

    // a result could be an adapted result from a parse tree (TreeNodeView)
    // or a calculated, named result (count,10)
    std::vector<TAdapter> adapted_results;
    std::vector<std::pair<std::string,std::string>> scalar_results;
    enum type{
        ADAPTED,
        SCALAR
    };
    std::vector<std::pair<type,unsigned int>> results;
//    std::vector<std::pair<type,Result>> results;
};
#include "waspsiren/SIRENResultSet.i.h"
} // end of namespace
#endif
