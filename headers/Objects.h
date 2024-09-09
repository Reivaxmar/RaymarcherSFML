#ifndef OBJECT_DEFINITIONS_H
#define OBJECT_DEFINITIONS_H

#include "Object2D.h"
#include <cmath>
#include "utils/Vec2utils.h"
namespace Objs
{
    class Circle : public Object2D {
    public:
        Circle(double radius, Vector2f pos, Color color = Color::White, int tex = -1)
            : m_radius(radius)
            , m_shape(radius)
        {
            info = ObjectInfo(color, tex);
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

        double getTexU(const Vector2f pos) const override {
            double x = atan2(pos.x - getPosition().x, pos.y - getPosition().y) / (M_PI * 2.0);
            if(x < 0)
                x++;
            return x;
        }
        
    private:
        CircleShape m_shape;
        double m_radius;
    };

    class Rect : public Object2D {
    public:
        Rect(Vector2f size, Vector2f pos, Color color = Color::White, int tex = -1)
            : m_size(size)
            , m_shape(size)
        {
            info = ObjectInfo(color, tex);
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

    class Line : public Object2D {
    public:
        Line(Vector2f from, Vector2f to, Color color = Color::White, int tex = -1)
            : m_A(from)
            , m_B(to)
        {
            info = ObjectInfo(color, tex);
        }

        virtual void draw(RenderTarget& target, RenderStates states) const {
            states.transform *= getTransform();
            // target.draw(m_shape, states);
        }

        virtual double getDistance(const Vector2f pos) const {
            // Vector from A to B
            Vector2f AB = m_B - m_A;
            // Vector from A to point
            Vector2f AP = pos - m_A;
            
            // Dot products
            float dotAB_AB = AB.x * AB.x + AB.y * AB.y; // AB . AB
            float dotAP_AB = AP.x * AB.x + AP.y * AB.y; // AP . AB
            
            // Projection scalar
            float t = dotAP_AB / dotAB_AB;
            
            // Clamp t to the range [0, 1] to stay within the segment
            t = std::max(0.f, std::min(1.f, t));
            
            // Find the closest point on the segment
            sf::Vector2f closestPoint = m_A + t * AB;
            
            // Compute the distance from the point to the closest point
            sf::Vector2f distanceVector = pos - closestPoint;
            return std::sqrt(distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);
        }

        double getTexU(const Vector2f pos) const override {
            Vector2f ab, ac;
            ab = m_B - m_A;
            ac = pos - m_A;
            return dotProduct(ac, ab) / dotProduct(ab, ab);
        }
        
    private:
        Vector2f m_A, m_B;
    };
} // namespace Objs



#endif