#ifndef WASP_DEFINITION_H
#define WASP_DEFINITION_H

#include "waspcore/wasp_bug.h"
#include "waspcore/decl.h"
#include <set>
#include <string>
#include <memory>
namespace wasp
{
/**
 * @brief The def_compare struct comparator for a set of Definition
 */
template<class D>
struct def_compare
{
    bool operator()(const D* lhs, const D* rhs) const
    {
        wasp_require(lhs);
        wasp_require(rhs);
        return lhs->name() < rhs->name();
    }
};
class WASP_PUBLIC AbstractDefinition
{
  public:
    typedef std::shared_ptr<AbstractDefinition> SP;
    virtual ~AbstractDefinition() {}
    virtual AbstractDefinition* create(const std::string& name) = 0;
    virtual AbstractDefinition* create_aliased(const std::string&  name,
                                               AbstractDefinition* def) = 0;
    virtual const std::string& name() const                             = 0;
    virtual bool has(const std::string& name) const                     = 0;
    virtual int delta(const std::string& name,
                      std::string&       actual_name) const        = 0;
    virtual AbstractDefinition* parent() const                     = 0;
    virtual AbstractDefinition* get(const std::string& name) const = 0;
    virtual const std::string& actual_name() const                 = 0;
};

class WASP_PUBLIC Definition : public AbstractDefinition
{
  public:
    Definition(const std::string& name = "");
    ~Definition();

    const std::string& name() const { return m_name; }
    const std::string& actual_name() const { return name(); }

    /**
     * @brief create creates a new definition mapped
     * @param name the name of the new definition relative to this definition
     * @return pointer to new Definition, or nullptr if collision occurs
     * Collisions occur then the given name is already assigned a definition
     */
    AbstractDefinition* create(const std::string& name);
    /**
     * @brief create_aliased creates a new aliased definition map
     * @param name the aliase name
     * @param definition the definition for which the alias is associated
     * @return the new AliasedDefinition
     */
    AbstractDefinition* create_aliased(const std::string&  name,
                                       AbstractDefinition* definition);
    template<class TreeView>
    Definition* create_from(const TreeView& view)
    {
        for (size_t i = 0; i < view.child_count(); ++i)
        {
            const auto& child_view       = view.child_at(i);
            Definition* child_definition = create(child_view.name());
            child_definition->create_from(child_view);
        }
        return this;
    }

    /**
     * @brief delta determine the definition section delta
     * @param name the name for which to search
     * @param actual_name the dealiased name of the definition (aname = name if
     * not an alias)
     * @return d=0  - the current level accepts the given named section
     *         d>0  - the parent level d levels up accepts.
     *         d=-1 - the named section is not accepted by this or any parent
     * definition
     */
    int delta(const std::string& name, std::string& actual_name) const;

    /**
     * @brief has determine if this definition the given child definition
     * @param name the name of the child definition to determine existence
     * @return true, iff the child definition is present.
     */
    bool has(const std::string& name) const;

    /**
     * @brief get acquire the requested definition
     * @param name the name of the requested definition
     * @return AbstractDefinition * - pointer to requested, nullptr iff no
     * definition with given name exists
     */
    AbstractDefinition* get(const std::string& name) const;

    /**
     * @brief parent acquires the parent definition of this definition
     * @return the parent - nullptr iff it has no parent
     */
    Definition* parent() const;

  private:
    std::string m_name;
    /**
     * @brief The encapsulating definition for this definition
     */
    Definition* m_parent;
    /**
     *  @brief Child node name to definition map
     */
    std::set<AbstractDefinition*, def_compare<AbstractDefinition>> m_children;
};
class WASP_PUBLIC AliasedDefinition : public AbstractDefinition
{
  public:
    AliasedDefinition(const std::string& name, AbstractDefinition* definition)
        : AbstractDefinition(), m_definition(definition), m_name(name)
    {
    }

    const std::string& name() const { return m_name; }
    const std::string& actual_name() const { return m_definition->name(); }

    AbstractDefinition* parent() const { return m_definition->parent(); }
    AbstractDefinition* get(const std::string& name) const
    {
        return m_definition->get(name);
    }
    bool has(const std::string& name) const { return m_definition->has(name); }
    int delta(const std::string& name, std::string& actual_name) const
    {
        return m_definition->delta(name, actual_name);
    }
    AbstractDefinition* create(const std::string& name)
    {
        return m_definition->create(name);
    }
    AbstractDefinition* create_aliased(const std::string&  name,
                                       AbstractDefinition* definition)
    {
        return m_definition->create_aliased(name, definition);
    }

  private:
    AbstractDefinition* m_definition;
    std::string         m_name;
};
}  // end of wasp namespace
#endif
