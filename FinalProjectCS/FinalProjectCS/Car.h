#ifndef CAR_H
#define CAR_H
#include <SFML/Graphics.hpp>
using namespace sf;
class Car : public Drawable
{
public:
	Car(const Color& color, const Vector2f& pos);
	void applyTexture();
	void handleInput(const Event& event);
	void update();
	static Texture cTexture;
	Sprite sShape;
	void reset();
protected:
	void draw(RenderTarget& car, const RenderStates states) const;
private:
	RectangleShape cShape;	
};
#endif CAR_H // end of CAR_H
