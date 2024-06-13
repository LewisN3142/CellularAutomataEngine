#include <sstream>
#include "InputHandler.h"

using namespace sf;

void InputHandler::initialiseInputHandler(std::vector<std::shared_ptr<Button>> buttons, View* pointerToUIView, Screen* parentScreen, ScreenManagerRemoteControl* sw)
{
	m_ScreenManagerRemoteControl = sw;
	m_Buttons = buttons;
	m_PointerToUIPanelView = pointerToUIView;
	m_ParentScreen = parentScreen;
}

void InputHandler::handleInput(RenderWindow& window, Event& event)
{
	if (event.type == Event::KeyPressed)
	{
		handleKeyPressed(window, event);
	}

	if (event.type == Event::KeyReleased)
	{
		handleKeyReleased(window, event);
	}

	if (event.type == Event::MouseButtonReleased)
	{
		//Check for click and release on buttons (implement similar for tiles but in screen not in UI View...)
		auto end = m_Buttons.end();

		for (auto i = m_Buttons.begin(); i != end; ++i)
		{
			if ((*i)->m_Collider.contains(window.mapPixelToCoords(Mouse::getPosition(), (*getPointerToUIView()))))
			{
				handleLeftClick(window, (*i)->m_Text);
				break;
			}
		}
	}
}

void InputHandler::handleKeyPressed(RenderWindow& window, Event& event)
{

}

void InputHandler::handleKeyReleased(RenderWindow& window, Event& event)
{

}

void InputHandler::handleLeftClick(RenderWindow& window, std::string& buttonInteractedWith)
{
	// Must be better way of doing this than using string, why not pass pointer to object?
}

View* InputHandler::getPointerToUIView()
{
	return m_PointerToUIPanelView;
}

ScreenManagerRemoteControl* InputHandler::getPointerToScreenManagerRemoteControl()
{
	return m_ScreenManagerRemoteControl;
}

Screen* InputHandler::getParentScreen()
{
	return m_ParentScreen;
}