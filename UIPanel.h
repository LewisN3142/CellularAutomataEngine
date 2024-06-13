#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

using namespace sf;

class UIPanel {
private:
	RectangleShape m_UIPanel;
	std::vector<std::shared_ptr<Button>> m_Buttons;

protected:
	float m_ButtonWidth = 0;
	float m_ButtonHeight = 0;
	float m_ButtonPadding = 0;

	Font m_Font;
	Text m_Text;

	void addButton(Vector2f position, float width, float height, Color buttonColor, std::string text);

public:
	View m_View;

	UIPanel(Vector2i res, Vector2f position, float UIWidth, float UIHeight, Color UIColor);

	std::vector<std::shared_ptr<Button>> getButtons();
	virtual void draw(RenderWindow& window);
};