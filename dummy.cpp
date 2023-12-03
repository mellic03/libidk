#include "libidk/libidk.hpp"

int main()
{
    idk::Allocator<int> v;
    v.create();

    std::cout << v.get(0);

    return 0;
}

