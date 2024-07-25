#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <vector>
#include <iostream>
#include <memory>
using namespace std;

#include "Objects.h"

struct CollideInfo {
    int objIdx;
    Vector2f pos;
    double dist;
};

class Scene : public Drawable {
public:
    Scene();
    Scene(const Scene&) = delete;             // Disable copy constructor
    Scene& operator=(const Scene&) = delete;  // Disable copy assignment
    Scene(Scene&&) noexcept = default;        // Enable move constructor
    Scene& operator=(Scene&&) noexcept = default; // Enable move assignment
    vector<shared_ptr<Object2D>> objs;
private:
    virtual void draw(RenderTarget& target, RenderStates states) const;
};

#endif