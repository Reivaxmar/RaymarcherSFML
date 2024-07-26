#include "Raymarcher.h"

Raymarcher::Raymarcher() {

}

void Raymarcher::Update() {
    // cout << "Updating..." << endl;
    // Reset the hitInfo vector
    hitInfo.resize(0);
}

void Raymarcher::draw(RenderTarget& target, RenderStates states) const {
    // Create a small red point
    CircleShape point(5);
    point.setFillColor(Color::Red);
    point.setOrigin(5, 5);
    // And for each ray
    for(int i = 0; i < hitInfo.size(); i++) {
        // If it doesn't collide, continue to the next one
        if(hitInfo[i].objIdx == -1) continue;
        // Else draw the hitpoint
        point.setPosition(hitInfo[i].pos);
        target.draw(point);
    }
}

CollideInfo Raymarcher::ShootRay(Vector2f from, double dir, Scene& scene) {
    // Define the maximum distance limits
    double minDist = 0.01;
    double maxDist = 10e3;
    double dist = 100;
    // And the index of the final collided object
    int objIdx = 0;

    Vector2f curPos = from;
    // While the circle is neither too small nor too big
    while(dist > minDist && dist < maxDist) {
        objIdx = 0;
        // Get the first distance
        dist = scene.objs[0]->getDistance(curPos);
        // And the minimum of all the others
        for(int i = 1; i < scene.objs.size(); i++) {
            double newDist = scene.objs[i]->getDistance(curPos);
            if(newDist < dist) {
                dist = newDist;
                objIdx = i;
            }
        }
        // Move the current position
        Vector2f addPos = Vector2f(cos(dir * DEG_TO_RAD) * dist, sin(dir * DEG_TO_RAD) * dist);
        curPos += addPos;
    }
    if(dist >= maxDist) {
        hitInfo.push_back(CollideInfo{-1, from, 0.0});
    } else {
        Vector2f deltaPos = curPos-from;
        double distFromO = sqrt(deltaPos.x*deltaPos.x+deltaPos.y*deltaPos.y);
        hitInfo.push_back(CollideInfo{objIdx, curPos, distFromO});
    }
    return hitInfo[hitInfo.size()-1];
}

void Raymarcher::Fisheye(double dir) {
    hitInfo[hitInfo.size()-1].dist *= cos(dir*DEG_TO_RAD);
}