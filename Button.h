#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Button
{
private:
	RectangleShape m_ButtonShape;
	Text m_ButtonText;
	Font m_Font;

public:
	std::string m_Text;
	FloatRect m_Collider;

	Button(Vector2f position, float width, float height, Color buttonColor, std::string text);
	void draw(RenderWindow& window);
};