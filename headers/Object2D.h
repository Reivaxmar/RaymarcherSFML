#ifndef OBJECT2D_CLASS_H
#define OBJECT2D_CLASS_H

#include <SFML/Graphics.hpp>
using namespace sf;
#include <optional>
using namespace std;

struct ObjectInfo {
    Color color;
    int texture;
    ObjectInfo(Color _c, int _t) : color(_c), texture(_t) {}
    ObjectInfo() {}
};

class Object2D : public Transformable, public Drawable {
public:
    virtual ~Object2D() = default;
    virtual double getDistance(const Vector2f pos) const = 0;
    virtual double getTexU(const Vector2f pos) const { return -1.0; }
    ObjectInfo info;
protected:
    virtual void draw(RenderTarget& target, RenderStates states) const override = 0;
};

#endif