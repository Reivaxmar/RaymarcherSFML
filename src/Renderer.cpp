#include "Renderer.h"

Renderer::Renderer(int FOV, int nRays)
    : m_FOV(FOV)
    , m_nRays(nRays)
{

}

void Renderer::draw(RenderTarget& target, Scene& scene) {
    // target.draw(m_raymarcher, states);
    RectangleShape shape;
    shape.setSize(Vector2f(target.getSize().x/(double)m_nRays, target.getSize().y));
    shape.setFillColor(Color::White);
    // And for each ray
    for(int i = 0; i < m_raymarcher.hitInfo.size(); i++) {
        // If it doesn't collide, continue to the next one
        if(m_raymarcher.hitInfo[i].objIdx == -1) continue;
        // Else draw the hitpoint
        // cout << m_raymarcher.hitInfo[i].objIdx << endl;
        // cout << shape.getSize().y*shape.getScale().y << endl;
        shape.setScale(Vector2f(1, 200.0/m_raymarcher.hitInfo[i].dist));
        shape.setPosition(Vector2f(i*shape.getSize().x, (target.getSize().y-shape.getGlobalBounds().height)/2.0));
        shape.setFillColor(scene.objs[m_raymarcher.hitInfo[i].objIdx]->info.color);
        target.draw(shape);
    }
}

void Renderer::draw(RenderTarget& target, RenderStates states) const {
    exit(-1);
}

void Renderer::Update(Scene& scene, Player player) {
    m_raymarcher.Update();
    for(double i = -m_FOV/2.0; i <= m_FOV/2.0; i += m_FOV/(double)m_nRays) {
        m_raymarcher.ShootRay(player.GetPosition(), player.GetRotation()+i, scene);
    }
}