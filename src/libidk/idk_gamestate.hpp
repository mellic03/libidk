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
private:
    friend class GameStateGroup;
    std::string     m_name;
    GameStateGroup *m_group;

public:
    GameState();

    void transition( const std::string &to );

    virtual void update() {  }
    virtual void enter( GameState *from ) {  }
    virtual void exit( GameState *to ) {  }

};



class idk::GameStateGroup
{
private:
    void state_assert( const std::string &name );

protected:
    std::map<std::string, GameState*> m_states;
    std::set<std::string>             m_active;

public:
    void addState( idk::GameState*, const std::string &name, bool active=false );
    void makeActive( const std::string &name );
    void makeInactive( const std::string &name );
    void transition( const std::string &from, const std::string &to );
    void update();

};

