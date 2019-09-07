#ifndef HEIGHTMAP_RENDERER_H
#define HEIGHTMAP_RENDERER_H

#include "Surface.h"

template<typename UnitT = uint8_t>
class Renderer {
    virtual ~Renderer() = default;

    virtual void render(Surface<UnitT> surf) = 0;
};

#endif //HEIGHTMAP_RENDERER_H
