#pragma once



namespace idk { class Identifiable; };


class idk::Identifiable
{
private:
    int m_id;

public:

    constexpr int ID() const { return m_id; };

};
