#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Raymarcher.h"

class Player : public Drawable {
public:
    Player(Vector2f pos);
    void Update(float dt);
    float GetRotation();
    Vector2f GetPosition();
private:
    virtual void draw(RenderTarget& target, RenderStates states) const;
    Vector2f m_pos;
    CircleShape m_shape;
    const int m_speed = 5;
    float m_rot;
};

#endif