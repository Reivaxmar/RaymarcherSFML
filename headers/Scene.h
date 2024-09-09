#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <vector>
#include <iostream>
#include <memory>
#include <fstream>
using namespace std;

#include "Objects.h"

struct CollideInfo {
    int objIdx;
    Vector2f pos;
    double dist;
    double u;
};

class Scene : public Drawable {
public:
    Scene();
    Scene(const Scene&) = delete;             // Disable copy constructor
    Scene& operator=(const Scene&) = delete;  // Disable copy assignment
    Scene(Scene&&) noexcept = default;        // Enable move constructor
    Scene& operator=(Scene&&) noexcept = default; // Enable move assignment
    void loadFromFile(string path);
    vector<shared_ptr<Object2D>> objs;
    vector<Texture> textures;
private:
    virtual void draw(RenderTarget& target, RenderStates states) const;
    void inCircle(ifstream& file);
    void inRect(ifstream& file);
    void inLine(ifstream& file);
};

#endif