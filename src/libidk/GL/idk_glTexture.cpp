#include "idk_glTexture.hpp"

#include "../idk_assert.hpp"
#include "../idk_math.hpp"
#include "../idk_log.hpp"




idk::TextureWrapper::TextureWrapper()
{

}


idk::TextureWrapper::TextureWrapper( uint32_t *pixels, size_t w, size_t h )
{
    m_data = std::make_shared<uint32_t[]>(w*h);
    std::memcpy(m_data.get(), pixels, w*h*sizeof(uint32_t));

    width  = w;
    height = h;
}



void*
idk::TextureWrapper::data()
{
    return (void *)(m_data.get());
}






static void deleter( uint32_t *p )
{
    if (p)
    {
        idk::gl::deleteTextures(1, p);
        delete p;
    }
}



idk::TextureRef::TextureRef()
:   m_texture(nullptr, deleter)
{

}


idk::TextureRef::TextureRef( uint32_t texture, size_t w, size_t h )
:   m_texture(new uint32_t(texture), deleter)
{
    width     = w;
    height    = h;
}


uint32_t
idk::TextureRef::ID()
{
    return *(m_texture.get());
};

