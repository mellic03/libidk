#pragma once

#include <vector>
#include <map>
#include <functional>


namespace idk
{
    template <typename ktype, typename dtype>
    class EventEmitter;
}


template <typename ktype, typename dtype>
class idk::EventEmitter
{
private:
    using fn_type = std::function<void(dtype)>;
    std::map<ktype, std::vector<fn_type>> m_events;

public:
    EventEmitter &on( const ktype &key, const fn_type &callback );
    void emit( const ktype &key, const dtype &data );
    void emit( const ktype &key );
};



template <typename ktype, typename dtype>
idk::EventEmitter<ktype, dtype>&
idk::EventEmitter<ktype, dtype>::on( const ktype &key, const fn_type &callback )
{
    m_events[key].push_back(callback);
    return *this;
}


template <typename ktype, typename dtype>
void
idk::EventEmitter<ktype, dtype>::emit( const ktype &key, const dtype &data )
{
    for (auto &callback: m_events[key])
    {
        callback(data);
    }
}


template <typename ktype, typename dtype>
void
idk::EventEmitter<ktype, dtype>::emit( const ktype &key )
{
    for (auto &callback: m_events[key])
    {
        callback(nullptr);
    }
}

