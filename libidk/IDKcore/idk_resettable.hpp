#pragma once


namespace idk
{
    template <typename ...Args>
    class Resettable
    {
        virtual void reset ( Args ...params ) = 0;
    };

};



