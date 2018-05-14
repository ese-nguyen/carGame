#include "Obstacle.h"
#include "Constants.h"
#include <SFML\Graphics.hpp>

using namespace sf;

Texture Obstacle::oTexture;
Obstacle::Obstacle(Type type, const Color& color, const Vector2f& pos)
{
	oType = Circle;
	oShape = std::unique_ptr<Shape>(new CircleShape(OBJECT_SIZE / 2.0f));		// Unique ptr is pointer to manage objects
	oShape->setTexture(&oTexture);
	oShape->setPosition(pos);
	oShape->setFillColor(color);
	oShape->setOrigin(oShape->getLocalBounds().width / 2, 0);
}

Shape& Obstacle::getShape()
{
	return *oShape;
}
Obstacle::Type Obstacle::getType()
{
	return oType;
}

void Obstacle::draw(RenderTarget& target, RenderStates states) const {
	target.draw(*oShape, states);
}