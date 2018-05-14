#include "Car.h"
#include "Constants.h"
#include <SFML\Graphics.hpp>
using namespace sf;

Texture Car::cTexture;

Car::Car(const Color& color, const Vector2f& pos):
	sShape()
{
	sShape.setColor(color);
	sShape.setOrigin(sShape.getGlobalBounds().width / 2, 0);
	sShape.setPosition(WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2);
	sShape.setScale(Vector2f(0.65, 0.65));
};

void Car::applyTexture() {

	sShape.setTexture(cTexture,false);
}
void Car::handleInput(const Event& event) {
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Key::Left 
		 && sShape.getPosition().x > LANE_WIDTH)
	{

		sShape.move(-70.0f, 0);
		sShape.setRotation(-10);
		sShape.setRotation(0);
	}
		
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Key::Right
		 && sShape.getPosition().x < LANE_WIDTH*3)
	{
		sShape.move(70.0f, 0);
		sShape.setRotation(10);
		sShape.setRotation(0);
	}
}
void Car::update() {
	sShape.setPosition(sShape.getPosition().x, WINDOW_HEIGHT-70);
}
void Car::reset(){
	sShape.setPosition(WINDOW_WIDTH / 2 + 12, WINDOW_HEIGHT / 2);
}

void Car::draw(RenderTarget& car, const RenderStates states) const {
	car.draw(sShape, states);
}