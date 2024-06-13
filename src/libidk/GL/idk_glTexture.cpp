#include "idk_glTexture.hpp"

#include "../idk_assert.hpp"
#include "../idk_math.hpp"
#include "../idk_log.hpp"




static void deleter( uint32_t *p )
{
    if (p)
    {
        LOG_INFO() << "Deleting texture " << *p;
        idk::gl::deleteTextures(1, p);
        delete p;
    }
}



idk::TextureRef::TextureRef()
:   m_texture(nullptr, deleter)
{
    LOG_INFO() << "idk::TextureRef::TextureRef()";
}


idk::TextureRef::TextureRef( uint32_t texture, size_t w, size_t h )
:   m_texture(new uint32_t(texture), deleter)
{
    LOG_INFO() << "idk::TextureRef::TextureRef( uint32_t, size_t, size_t )";
    width     = w;
    height    = h;
}


uint32_t
idk::TextureRef::ID()
{
    return *(m_texture.get());
};

