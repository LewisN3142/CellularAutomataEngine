#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "InputHandler.h"
#include "UIPanel.h"
#include "ScreenManagerRemoteControl.h"

class InputHandler;

class Screen {
private:
	std::vector<std::shared_ptr<InputHandler>> m_InputHandlers;
	std::vector<std::unique_ptr<UIPanel>> m_Panels;

protected:
	void addPanel(std::unique_ptr<UIPanel> panel, ScreenManagerRemoteControl* smrc, std::shared_ptr<InputHandler> inputHandler);

public:
	virtual void initialise();
	virtual void update(float fps);
	virtual void draw(RenderWindow& window);
	void handleInput(RenderWindow& window);

	View m_View;
};

