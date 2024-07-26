#include "Player.h"

Player::Player(Vector2f pos) 
    : m_pos(pos)
    , m_shape(5.f)
    , m_rot(0)
{
    // Center the point at its origin
    m_shape.setOrigin(Vector2f(m_shape.getRadius(), m_shape.getRadius()));
}

void Player::Update(float dt) {
    double toRot = (Keyboard::isKeyPressed(Keyboard::Right) - Keyboard::isKeyPressed(Keyboard::Left));
    m_rot += toRot * dt;
    m_shape.setRotation(m_rot);

    Vector2f toMove;
    toMove.y = (Keyboard::isKeyPressed(Keyboard::A) - Keyboard::isKeyPressed(Keyboard::D)) * m_speed;
    toMove.x = (Keyboard::isKeyPressed(Keyboard::S) - Keyboard::isKeyPressed(Keyboard::W)) * m_speed;

    float rotation = m_shape.getRotation() * DEG_TO_RAD; // Convert rotation to radians

    // Calculate rotated movement vector
    float cosTheta = cos(rotation);
    float sinTheta = sin(rotation);

    toMove = Vector2f(
        -toMove.x * cosTheta + toMove.y * sinTheta,
        -toMove.x * sinTheta - toMove.y * cosTheta);

    m_pos += toMove * dt;
    m_shape.setPosition(m_pos);

}

void Player::draw(RenderTarget& target, RenderStates states) const {
    target.draw(m_shape);
    RectangleShape line(Vector2f(200, 5));
    line.setPosition(m_pos);
    line.setRotation(m_rot);
    target.draw(line);
}

float Player::GetRotation() {
    return m_rot;
}

Vector2f Player::GetPosition() {
    return m_pos;
}