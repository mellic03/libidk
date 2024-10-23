#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>


namespace idk
{
    class GameState;
    class GameStateGroup;
}



class idk::GameState
{
public:
    const std::string m_name;
    GameStateGroup *m_group;

    GameState( const std::string&, idk::GameStateGroup* );

    void transition( const std::string &to );

    virtual void update() {  }
    virtual void enter( GameState *from ) {  }
    virtual void exit( GameState *to ) {  }

};


class idk::GameStateGroup
{
private:
    std::map<std::string, GameState*> m_states;
    std::set<std::string>             m_active;

    void state_assert( const std::string &name );

public:
    void addState( idk::GameState* );
    void makeActive( const std::string &name );
    void makeInactive( const std::string &name );
    void transition( const std::string &from, const std::string &to );
    void update();

};

