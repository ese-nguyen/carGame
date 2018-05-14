#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <memory>
#include <SFML/Graphics.hpp>
using namespace sf;
class Obstacle : public Drawable
{
public:
	enum Type{Circle};
	Obstacle::Obstacle(Type type, const Color& color, const Vector2f& pos);
	Shape& getShape();
	Type getType();
	static Texture oTexture;
protected:
	void draw(RenderTarget& target, RenderStates states) const;
	Type oType;
	std::unique_ptr<Shape> oShape;
};
#endif OBSTACLE_H  //End of OBSTACLE_H