#include "Game.h"
#include <cstdlib>
#include <iterator>
#include <iostream>
#include <fstream>

Game::Game() :
	gwindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "NHS TEAM", Style::Close | Style::Resize),
	NHScar(cColor, Vector2f{ LANE_WIDTH * 2,WINDOW_HEIGHT }),
	glanes(Lines, 6),
	overlay({ LANE_WIDTH * 4,WINDOW_HEIGHT }),
	playing(false)
{
	// Set vertical sync and frame rate
	gwindow.setVerticalSyncEnabled(true);
	gwindow.setFramerateLimit(60);

	// Create lanes;	
	glanes[0] = Vertex(Vector2f(LANE_WIDTH, 0), Color(180, 180, 180));
	glanes[1] = Vertex(Vector2f(LANE_WIDTH, WINDOW_HEIGHT), Color(180, 180, 180));
	glanes[2] = Vertex(Vector2f(LANE_WIDTH * 3, 0), Color(180, 180, 180));
	glanes[3] = Vertex(Vector2f(LANE_WIDTH * 3, WINDOW_HEIGHT), Color(180, 180, 180));
	glanes[4] = Vertex(Vector2f(LANE_WIDTH * 2, 0), Color(180, 180, 180));
	glanes[5] = Vertex(Vector2f(LANE_WIDTH * 2, WINDOW_HEIGHT), Color(180, 180, 180));

	//Set up all things
		// Notifications
	NHSfont.loadFromFile("UTM Azuki.ttf");
	NHSnoti.setFont(NHSfont);
	NHSnoti.setFillColor(Color(180, 180, 180));
	NHSnoti.setCharacterSize(13);
	NHSnoti.setString("Avoid all circles. Press Space to continue");
	NHSnoti.setPosition((gwindow.getSize().x - NHSnoti.getLocalBounds().width) / 2.f,
		(gwindow.getSize().y - NHSnoti.getLocalBounds().height) / 2.f);
	// Display score
	NHSdScore.setFont(NHSfont);
	NHSdScore.setPosition(WINDOW_WIDTH / 2, 30);
	NHSdScore.setOrigin(NHSdScore.getGlobalBounds().width / 2, NHSdScore.getGlobalBounds().height / 2);
	overlay.setFillColor(Color(0, 0, 0, 100));
	// Car, Obstacles, Music
	Obstacle::oTexture.loadFromFile("circle.png");
	Obstacle::oTexture.setSmooth(true);
	Car::cTexture.loadFromFile("car.png");
	Car::cTexture.setSmooth(true);
	NHScar.applyTexture();
	NHScar.reset();
	if (!music.openFromFile("16-bit-Harebell.wav"))
		printf("Error loading Music");
	music.setLoop(true);

}

void Game::newGame() {
	//music.play();
	NHSobs.clear();
	NHSscore = 1 - OBJS_ON_SCREEN / 2;
	velocity = INITIAL_VELOCITY;
	distance = SPAWN_DIST;
	playing = true;
	NHScar.reset();
}

void Game::run() {
	srand(time(nullptr));
	// Events with windows
	while (gwindow.isOpen()) {
		Event evnt;
		while (gwindow.pollEvent(evnt)) {
			switch (evnt.type)
			{
			case Event::Closed:
				gwindow.close();
				break;
			case Event::Resized:
				printf("New window size is %d * %d", evnt.size.width, evnt.size.height);
				break;
			case Event::TextEntered:
				if (evnt.text.unicode < 128)
					printf("%c", evnt.text.unicode);
				break;
			}
			if (playing)
				NHScar.handleInput(evnt);
			else if (evnt.type == Event::KeyReleased && evnt.key.code == Keyboard::Space) {
				playing = true;
				newGame();
			}
		}
		auto dt = NHStimer.restart().asSeconds();
		if (playing) {
			velocity += ACCELERATION * dt;
			distance += velocity * dt;

			if (distance > SPAWN_DIST)
			{
				++NHSscore;
				NHSobs.emplace_front(Obstacle::Circle, oColor, Vector2f{ LANE_WIDTH / 2.f + LANE_WIDTH * (rand() % 2), 0 });
				NHSobs.emplace_front(Obstacle::Circle, oColor, Vector2f{ LANE_WIDTH * 2.f + LANE_WIDTH / 2 + LANE_WIDTH * (rand() % 2), 0 });
				distance -= SPAWN_DIST;
			}

			for (auto it = NHSobs.begin(); it != NHSobs.end(); ++it)
			{
				it->getShape().move(0, velocity * dt);
				if (it->getShape().getGlobalBounds().top > WINDOW_HEIGHT - CAR_HEIGHT - OBJECT_SIZE
					&& it->getShape().getGlobalBounds().top < WINDOW_HEIGHT - OBJECT_SIZE) {
					if (it->getShape().getGlobalBounds().intersects(NHScar.sShape.getGlobalBounds()))
					{
						gameOver();
						std::cout << "That was closed!! Maybe next time!!" << std::endl;
						break;
					}
					std::cout << "Well played!!" << std::endl;
					it = std::prev(NHSobs.erase(it));
				}
			}
			//Update position after a game loop
			NHScar.update();
		}
		
		//Display data
		NHSdScore.setString(std::to_string(NHSscore));
		gwindow.clear(background);
		gwindow.draw(glanes);
		gwindow.draw(NHSdScore);
		for (auto& obs : NHSobs)
			gwindow.draw(obs);
		gwindow.draw(NHScar);
		if (!playing) {
			gwindow.draw(overlay);
			gwindow.draw(NHSnoti);
		}
		gwindow.display();
	}
}

void Game::gameOver() {
	playing = false;
	NHSnoti.setString("You score " + std::to_string(NHSscore) + ".\nPress Space to continue");
	NHSnoti.setPosition(0, (gwindow.getSize().y - NHSnoti.getLocalBounds().height) / 2.0f);
}