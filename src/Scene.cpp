#include "Scene.h"

Scene::Scene()
    : textures(0)
 {}

void Scene::draw(RenderTarget& target, RenderStates states) const {
    for (const auto& obj : objs) {
        target.draw(*obj, states); // Correctly access the draw method
    }
}


void Scene::loadFromFile(string path) {
    ifstream file(path);
    int numTexs;
    file >> numTexs;
    file.ignore();
    string texPath;
    Texture t;
    for(int i = 0; i < numTexs; i++) {
        getline(file, texPath);
        t.loadFromFile(texPath);
        textures.push_back(t);
    }

    int numObjs;
    file >> numObjs;

    for(int i = 0; i < numObjs; i++) {
        string s;
        file >> s;
        if(s == "Circle") {
            inCircle(file);
        } else if(s == "Rect") {
            inRect(file);
        } else if(s == "Line") {
            inLine(file);
        } else { // Not implemented
            cerr << "Object of type \"" << s << "\" not implemented!" << endl;
        }
    }

    file.close();
}


void Scene::inCircle(ifstream& file) {
    // Define the values
    double rad;
    Vector2f pos;
    int r, g, b;
    Color color;
    int texIdx;

    // Get them from the file
    file >> rad >> pos.x >> pos.y >> r >> g >> b >> texIdx;
    color = Color(r, g, b);

    // And finally add the object to the list
    objs.push_back(make_shared<Objs::Circle>(rad, pos, color, texIdx));

    file.ignore();
}

void Scene::inRect(ifstream& file) {
    // TODO
}

void Scene::inLine(ifstream& file) {
    // Define the values
    Vector2f a, b;
    int r, g, bl;
    Color color;
    int texIdx;

    // Get them from the file
    file >> a.x >> a.y >> b.x >> b.y >> r >> g >> bl >> texIdx;
    color = Color(r, g, bl);

    // And finally add the object to the list
    objs.push_back(make_shared<Objs::Line>(a, b, color, texIdx));

    file.ignore();
}