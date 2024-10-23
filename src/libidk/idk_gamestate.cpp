#include "idk_gamestate.hpp"
#include "./idk_assert.hpp"



idk::GameState::GameState( const std::string &n, idk::GameStateGroup *g )
:   m_name(n),
    m_group(g)
{

}


void
idk::GameState::transition( const std::string &to )
{
    m_group->transition(m_name, to);
}




void
idk::GameStateGroup::state_assert( const std::string &name )
{
    std::string msg = "State \"" + name + "\" does not exist";

    IDK_ASSERT(
        msg.c_str(),
        m_states.contains(name)
    );
}


void
idk::GameStateGroup::addState( idk::GameState *state )
{
    const auto &name = state->m_name;
    std::string msg = "State \"" + name + "\" already exists";

    IDK_ASSERT(
        msg.c_str(),
        m_states.contains(name) == false
    );

    m_states[name] = state;
}


void
idk::GameStateGroup::makeActive( const std::string &name )
{
    state_assert(name);
    m_active.insert(name);
}


void
idk::GameStateGroup::makeInactive( const std::string &name )
{
    state_assert(name);
    m_active.erase(name);
}


void
idk::GameStateGroup::transition( const std::string &from, const std::string &to )
{
    state_assert(from);
    state_assert(to);

    auto *A = m_states[from];
    auto *B = m_states[to];
    
    A->exit(B);
    B->enter(A);
}


void
idk::GameStateGroup::update()
{
    for (const auto &name: m_active)
    {
        m_states[name]->update();
    }
}



