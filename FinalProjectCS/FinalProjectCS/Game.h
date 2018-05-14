#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <deque>
#include <memory>
#include <algorithm>
#include "Obstacle.h"
#include "Constants.h"
#include "Car.h"
using namespace sf;
class Game
{
public:
	Game();
	void run();
private:
	void newGame();
	void gameOver();
	
	sf::RenderWindow gwindow;					// Window

	sf::VertexArray glanes;						// Lanes
	std::deque<Obstacle> NHSobs;				// Obstacle ....... <deque> is used to insert object, clear object
	Car NHScar;									// Player

	sf::Clock NHStimer;							// Timer
	sf::Music music;							// Music

	sf::Font NHSfont;							// Font
	sf::Text NHSnoti;							// Notification
	sf::Text NHSdScore;							// Display Score
	sf::RectangleShape overlay;					// Overlay

	int NHSscore;								// Score
	bool playing;								// Check if game over or not
	float distance, velocity;					// To create new obstacles and increase velocity
};

#endif // GAME_H