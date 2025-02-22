#pragma once

#include <libidk/idk_assert.hpp>
#include <array>
#include <vector>
#include <map>
#include <functional>
#include <type_traits>


namespace idk
{
    template <typename ktype, typename dtype=void>
    class EventEmitter;

    template <typename ktype, typename dtype=void, int capacity=32>
    class EventEmitterIndexed;
}


template <typename ktype, typename dtype>
class idk::EventEmitter
{
private:
    using fn_type = std::conditional_t<
        std::is_same_v<dtype, void>,
        std::function<void()>,
        std::function<void(dtype*)>
    >;

    std::map<ktype, std::vector<fn_type>> m_events;

public:
    auto &on( const ktype &key, const fn_type &callback )
    {
        m_events[key].push_back(callback);
        return *this;
    }

    void emit( const ktype &key, dtype *data=nullptr )
    {
        for (auto &callback: m_events[key])
        {
            if constexpr (std::is_same_v<dtype, void>)
            {
                callback();
            }

            else
            {
                callback(data);
            }
        }
    }
};



template <typename ktype, typename dtype, int capacity>
class idk::EventEmitterIndexed
{
private:
    using fn_type = std::conditional_t<
        std::is_same_v<dtype, void>,
        std::function<void()>,
        std::function<void(dtype*)>
    >;

    std::array<std::vector<fn_type>, capacity> m_events;

public:
    auto &on( const ktype &key, const fn_type &callback )
    {
        IDK_ASSERT("Key must be < capacity", 0 <= key && key < capacity);
        m_events[key].push_back(callback);
        return *this;
    }

    void emit( const ktype &key, dtype *data=nullptr )
    {
        IDK_ASSERT("Key must be < capacity", 0 <= key && key < capacity);
        for (auto &callback: m_events[key])
        {
            if constexpr (std::is_same_v<dtype, void>)
            {
                callback();
            }

            else
            {
                callback(data);
            }
        }
    }
};
