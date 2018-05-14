#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics/Color.hpp>
#include <SFML\Graphics.hpp>

const float WINDOW_WIDTH = 280.0f;
const float WINDOW_HEIGHT = 512.0f;
const float LANE_WIDTH = 70.0f;
const float OBJECT_SIZE = LANE_WIDTH / 2;
const float CAR_HEIGHT = LANE_WIDTH;
const float SPAWN_DIST = 250;
const float INITIAL_VELOCITY = 220;
const float ACCELERATION = 5;
const float OBJS_ON_SCREEN = 1 + WINDOW_HEIGHT / (SPAWN_DIST + OBJECT_SIZE);

const sf::Color cColor = sf::Color::Red;
const sf::Color oColor = sf::Color::Yellow;
const sf::Color background = sf::Color::Magenta;

#endif // end of CONSTANTS_H