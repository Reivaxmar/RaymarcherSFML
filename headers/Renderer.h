#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Raymarcher.h"

class Renderer : public Drawable {
public:
    Renderer(int FOV, int nRays);
    void Update(Scene& scene, Player player);
    void draw(RenderTarget& target, Scene& scene);
private:
    virtual void draw(RenderTarget& target, RenderStates states) const;
    Raymarcher m_raymarcher;
    int m_FOV;
    int m_nRays;

};

#endif