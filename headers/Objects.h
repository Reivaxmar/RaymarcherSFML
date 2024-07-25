#ifndef OBJECT_DEFINITIONS_H
#define OBJECT_DEFINITIONS_H

#include "Object2D.h"
#include <cmath>

class Circle : public Object2D {
public:
    Circle(double radius, Vector2f pos, Color color = Color::White)
        : m_radius(radius)
        , m_shape(radius)
    {
        info = ObjectInfo{color};
        m_shape.setOrigin(m_radius, m_radius);
        setPosition(pos);
    }

    virtual void draw(RenderTarget& target, RenderStates states) const {
        states.transform *= getTransform();
        target.draw(m_shape, states);
    }

    virtual double getDistance(const Vector2f pos) const {
        Vector2f dist = getPosition() - pos;
        double length = sqrt(dist.x*dist.x + dist.y*dist.y);
        return length - m_radius;
    }
    
private:
    CircleShape m_shape;
    Vector2f m_pos;
    double m_radius;
};

#endif