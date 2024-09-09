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
        if(m_raymarcher.hitInfo[i].dist < 0) continue;
        // Else draw the hitpoint
        shape.setScale(Vector2f(1, 200.0/m_raymarcher.hitInfo[i].dist));
        shape.setPosition(Vector2f(i*shape.getSize().x, (target.getSize().y-shape.getGlobalBounds().height)/2.0));
        // Add the colors and the texture
        addColor(shape, scene, m_raymarcher.hitInfo[i]);

        // Finally draw the line
        target.draw(shape);
    }
}

void Renderer::addColor(RectangleShape& line, Scene& scene, CollideInfo c_info) {
    // Paint the line the color it is set
    line.setFillColor(scene.objs[c_info.objIdx]->info.color);
    // Get the texture u (like the uv but 1d)
    c_info.u = scene.objs[c_info.objIdx]->getTexU(c_info.pos);

    line.setTextureRect(IntRect(600, 600, 1, 1));

    // If it doesn't have a uv function implemented, return
    if(c_info.u < -0.0001) // Equals -1, but floating point accuracy
        return;
    
    // If there's no texture applied, return too
    if(scene.objs[c_info.objIdx]->info.texture == -1)
        return;

    line.setTexture(&scene.textures[scene.objs[c_info.objIdx]->info.texture]);
    Vector2u texSize = scene.textures[scene.objs[c_info.objIdx]->info.texture].getSize();
    line.setTextureRect(IntRect(c_info.u*texSize.x, 0, 1, texSize.y));
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
