#include "Renderer.h"

Renderer::Renderer(int FOV, int nRays)
    : m_FOV(FOV)
    , m_nRays(nRays)
{

}

void Renderer::draw(RenderTarget& target, Scene& scene) {
    RectangleShape shape;
    shape.setSize(Vector2f(target.getSize().x/(double)m_nRays, target.getSize().y));
    shape.setFillColor(Color::White);
    // And for each ray
    for(int i = 0; i < m_raymarcher.hitInfo.size(); i++) {
        // If it doesn't collide, continue to the next one
        if(m_raymarcher.hitInfo[i].objIdx == -1) continue;
        // Else draw the hitpoint
        shape.setScale(Vector2f(1, 200.0/m_raymarcher.hitInfo[i].dist));
        shape.setPosition(Vector2f(i*shape.getSize().x, (target.getSize().y-shape.getGlobalBounds().height)/2.0));
        shape.setFillColor(scene.objs[m_raymarcher.hitInfo[i].objIdx]->info.color);
        target.draw(shape);
    }
    // target.draw(m_raymarcher);
}

void Renderer::draw(RenderTarget& target, RenderStates states) const {
    exit(-1); // This shouldn't happen
}

void Renderer::Update(Scene& scene, Player player) {
    m_raymarcher.Update();
    double halfFOV = m_FOV / 2.0 * DEG_TO_RAD;

    for (int x = 0; x < m_nRays; ++x) {
        // Convert to NDC
        double ndc = (2.0 * x / (double)m_nRays) - 1.0;

        // Apply perspective correction
        double rayAngle = atan(ndc * tan(halfFOV)) / DEG_TO_RAD;

        // Cast the ray
        m_raymarcher.ShootRay(player.GetPosition(), player.GetRotation() + rayAngle, scene);
        m_raymarcher.Fisheye(rayAngle);
    }
}
