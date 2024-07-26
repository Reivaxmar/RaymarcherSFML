#ifndef OBJECT_DEFINITIONS_H
#define OBJECT_DEFINITIONS_H

#include "Object2D.h"
#include <cmath>
namespace Objs
{
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
        double m_radius;
    };

    class Rect : public Object2D {
    public:
        Rect(Vector2f size, Vector2f pos, Color color = Color::White)
            : m_size(size)
            , m_shape(size)
        {
            info = ObjectInfo{color};
            m_shape.setOrigin(size/2.f);
            setPosition(pos);
        }

        virtual void draw(RenderTarget& target, RenderStates states) const {
            states.transform *= getTransform();
            target.draw(m_shape, states);
        }

        virtual double getDistance(const Vector2f pos) const {
            Vector2f offset = Vector2f(abs(pos.x-getPosition().x), abs(pos.y-getPosition().y)) - m_size/2.f;
            Vector2f ud = Vector2f(max(offset.x, 0.f), max(offset.y, 0.f));
            float unsignedDst = sqrt(ud.x*ud.x+ud.y*ud.y);
            float distInsideBox = max(min(offset.x, 0.f), min(offset.y, 0.f));
            return unsignedDst + distInsideBox;
        }
        
    private:
        RectangleShape m_shape;
        Vector2f m_size;
    };
} // namespace Objs



#endif