#include "waspcore/Definition.h"

using namespace wasp;

Definition::Definition(const std::string &name)
    : AbstractDefinition(), m_name(name), m_parent(nullptr)
{
}

Definition::~Definition()
{
    for (auto pair : m_children)
        delete pair;
}

AbstractDefinition *Definition::create(const std::string &name)
{
    Definition *definition = new Definition(name);
    wasp_ensure(definition);
    definition->m_parent = this;
    auto success         = m_children.insert(definition);
    if (!success.second)
    {
        delete definition;
        definition = nullptr;
    }
    return definition;
}

AbstractDefinition *Definition::create_aliased(const std::string & name,
                                               AbstractDefinition *definition)
{
    wasp_require(definition);
    // Aliased node must have the same parent as the aliasee
    wasp_require(definition->parent() == this);
    auto *aliased = new AliasedDefinition(name, definition);
    wasp_ensure(aliased);
    auto success = m_children.insert(aliased);
    if (!success.second)
    {
        delete aliased;
        aliased = nullptr;
    }
    return aliased;
}

bool Definition::has(const std::string &name) const
{
    Definition def(name);
    return m_children.find(&def) != m_children.end();
}

int Definition::delta(const std::string &name, std::string &actual_name) const
{
    int level = 0;

    const Definition *def = this;

    while (def != nullptr)
    {
        auto named_def = def->get(name);
        if (named_def != nullptr)
        {
            actual_name = named_def->actual_name();
            return level;
        }
        ++level;
        def = def->m_parent;
    }
    return -1;  // couldn't find
}

AbstractDefinition *Definition::get(const std::string &name) const
{
    Definition def(name);
    auto       itr = m_children.find(&def);
    if (itr == m_children.end())
        return nullptr;
    return *itr;
}

Definition *Definition::parent() const
{
    return m_parent;
}
