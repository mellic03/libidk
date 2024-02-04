#pragma once

#include "idk_module.hpp"
#include "idk_scene_file.hpp"

namespace idk
{
    class Engine;
    class ComponentSystem;
};



/**
 * ## Dependency-related methods are only called if IDK_DEBUG is defined
*/

class idk::ComponentSystem: public idk::Module
{
public:
    virtual         ~ComponentSystem() = default;

    /*              Called when the component is assigned. */
    virtual void    onObjectAssignment( int obj_id, idk::Engine & ) = 0;

    /*              Called when the component is removed. */
    virtual void    onObjectDeassignment ( int obj_id, idk::Engine & ) = 0;

    /*              Called when a new game object is created. */
    virtual void    onObjectCreation( int obj_id, idk::Engine & ) = 0;

    /*              Called when a game object is deleted. */
    virtual void    onObjectDeletion( int obj_id, idk::Engine & ) = 0;

    /*              Called when a game object is created by copy. */
    virtual void    onObjectCopy( int src_obj_id, int dest_obj_id, idk::Engine & ) = 0;


    /*              Called when the EditorUI module is used to inspect a given game object */
    virtual void    onObjectSelection( int obj_id ) {  };


    virtual idk::CSFile onObjectSerialization   ( int obj_id )  { return idk::CSFile(); };
    virtual void        onObjectDeserialization ( idk::CSFile ) {  };


    virtual idk::CSFile onFileSave( idk::Engine & ) { return {0, nullptr, 0}; };
    virtual void        onFileLoad( idk::Engine &, const idk::CSFile & ) {  };

    virtual void        luaExpose( void *Lmod ) {  };


};


