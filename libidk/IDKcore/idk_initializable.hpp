#pragma once


namespace idk
{
    template <typename ...Args>
    class Initializable
    {
        virtual void init  ( Args  ...params ) = 0;
    };

};



