#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include "ScreenManagerRemoteControl.h"

using namespace sf;

class Screen;

class InputHandler
{
private:
	Screen* m_ParentScreen;;
	std::vector<std::shared_ptr<Button>> m_Buttons;
	View* m_PointerToUIPanelView;
	ScreenManagerRemoteControl* m_ScreenManagerRemoteControl;

public:
	void initialiseInputHandler(std::vector<std::shared_ptr<Button>> buttons, View* pointerToUIView, Screen* parentScreen, ScreenManagerRemoteControl* sw);
	void handleInput(RenderWindow& window, Event& event);

	virtual void handleKeyPressed(RenderWindow& window, Event& event);
	virtual void handleKeyReleased(RenderWindow& window, Event& event);
	virtual void handleLeftClick(RenderWindow& window, std::string& buttonInteractedWith); // Better way to do this than using strings... probably colliders as not only interacting with buttons, also tiles.

	View* getPointerToUIView();

	ScreenManagerRemoteControl* getPointerToScreenManagerRemoteControl();

	Screen* getParentScreen(); 
};