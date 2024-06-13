#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class ViewPanel
{
private:
	FloatRect m_ClipPanel;
	FloatRect m_ViewportScale;
	View m_PanelViewport;

public:
	ViewPanel(FloatRect clipPanel, FloatRect viewportScale);

	FloatRect getClipPanel();
	FloatRect getViewportScale();

	void setClipPanel(FloatRect clipPanel);
	void setViewportScale(FloatRect viewportScale);
	void setViewportDraw(RenderWindow& window);
};