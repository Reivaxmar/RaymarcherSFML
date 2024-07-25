#include "Scene.h"

Scene::Scene() {}

void Scene::draw(RenderTarget& target, RenderStates states) const {
    for (const auto& obj : objs) {
        target.draw(*obj, states); // Correctly access the draw method
    }
}
