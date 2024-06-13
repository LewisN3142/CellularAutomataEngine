#pragma once
#include "Screen.h"
#include "SimulationInputHandler.h"

class SimulationScreen :public Screen {
private:
	ScreenManagerRemoteControl* m_ScreenManagerRemoteControl;
	std::shared_ptr<SimulationInputHandler> m_SimInputHandler;

	Texture m_BackgroundTexture;
	Sprite m_BackgroundSprite;

public:
	SimulationScreen(Vector2i res, ScreenManagerRemoteControl* smrc);
	void initialise() override;
	void virtual update(float fps);
	void virtual draw(RenderWindow& window);
};