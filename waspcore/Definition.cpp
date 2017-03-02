#include "waspcore/Definition.h"


using namespace wasp;

Definition::Definition() : m_parent(nullptr)
{

}

Definition::Definition(const Definition &orig)
    : m_parent(nullptr)
{
    for( auto pair : orig.m_children)
    {
        auto * ptr = pair.second->clone();
        ptr->m_parent = this;
        m_children[pair.first] = ptr;
    }
}

Definition::~Definition()
{
    for( auto pair : m_children ) delete pair.second;
}

Definition * Definition::clone() const
{
    return new Definition(*this);
}



Definition * Definition::create(const std::string &name)
{
    auto itr = m_children.find(name);
    if( itr != m_children.end() ) return nullptr;
    Definition * definition = new Definition();
    wasp_ensure ( definition );

    m_children[name] = definition;
    return definition;
}

bool Definition::has(const std::string &name)const
{
    return m_children.find(name) != m_children.end();
}

int Definition::delta(const std::string & name)const{

    int level = 0;

    const Definition * def = this;

    while( def != nullptr )
    {
        if( def->has(name) ) return level;
        ++level;
        def = def->m_parent;
    }
    return -1; // couldn't find
}
