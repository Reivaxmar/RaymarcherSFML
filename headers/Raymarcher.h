#ifndef RAYMARCHER_CLASS_H
#define RAYMARCHER_CLASS_H

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
using namespace sf;
using namespace std;

#define DEG_TO_RAD (M_PI / 180.0)

#include "Scene.h"
#include "Player.h"

class Raymarcher : public Drawable {
public:
    Raymarcher();
    void Update();
    CollideInfo ShootRay(Vector2f from, double dir, Scene& scene);
    void Fisheye(double dir);
    vector<CollideInfo> hitInfo;
private:
    virtual void draw(RenderTarget& target, RenderStates states) const;
    vector<pair<Vector2f, double>> m_circles;
    double smoothMin(double a, double b, double k = 100);
};

#endif