#ifndef OBJECT2D_CLASS_H
#define OBJECT2D_CLASS_H

#include <SFML/Graphics.hpp>
using namespace sf;

struct ObjectInfo {
    Color color;
};

class Object2D : public Transformable, public Drawable {
public:
    virtual ~Object2D() = default;
    virtual double getDistance(const Vector2f pos) const = 0;
    ObjectInfo info;
protected:
    virtual void draw(RenderTarget& target, RenderStates states) const override = 0;
};

#endif