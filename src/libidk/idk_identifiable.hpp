#pragma once



namespace idk
{
    class Identifiable;
};


class idk::Identifiable
{
private:

public:
    int m_id;

    Identifiable( int id ): m_id(id) {  };
    constexpr int ID() const { return m_id; };

};


class idk_TestClass: public idk::Identifiable
{
private:

public:
    idk_TestClass( int id ): Identifiable(id) {  };

};
