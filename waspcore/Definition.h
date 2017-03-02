#ifndef WASP_DEFINITION_H
#define WASP_DEFINITION_H

#include "waspcore/wasp_bug.h"
#include <map>
#include <memory>
namespace wasp{
class Definition {
public:
    typedef std::shared_ptr<Definition> SP;
    Definition();
    Definition(const Definition& orig);
    ~Definition();

    Definition * clone()const;

    /**
     * @brief create creates a new definition mapped
     * @param name the name of the new definition relative to this definition
     * @return pointer to new Definition, or nullptr if collision occurs
     * Collisions occur then the given name is already assigned a definition
     */
    Definition * create(const std::string & name);

    /**
     * @brief delta determine the definition section delta
     * @return d=0  - the current level accepts the given named section
     *         d>0  - the parent level d levels up accepts.
     *         d=-1 - the named section is not accepted by this or any parent definition
     */
    int delta(const std::string & name)const;

    /**
     * @brief has determine if this definition the given child definition
     * @param name the name of the child definition to determine existence
     * @return true, iff the child definition is present.
     */
    bool has( const std::string & name )const;

private:
    Definition * m_parent;
    std::map<std::string,Definition*> m_children;

};
}
#endif
