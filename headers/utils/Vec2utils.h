#ifndef UTILS_VEC2
#define UTILS_VEC2

#include <SFML/Graphics.hpp>

template <typename T>
inline double dotProduct(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return static_cast<double>(a.x) * static_cast<double>(b.x) + 
           static_cast<double>(a.y) * static_cast<double>(b.y);
}

#endif