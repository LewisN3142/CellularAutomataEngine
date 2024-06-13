#include "ViewPanel.h"
// add in functionality to zoom out of tiling view and add more tiles - make view boxes variables for clipping when generating tiling

ViewPanel::ViewPanel(FloatRect clipPanel, FloatRect viewportScale)
{
	m_ClipPanel = clipPanel; // 
	m_ViewportScale = viewportScale; // What portion of the screen can be drawn to
	m_PanelViewport = View(clipPanel);
	m_PanelViewport.setViewport(m_ViewportScale);
}

FloatRect ViewPanel::getClipPanel()
{
	return m_ClipPanel;
}

FloatRect ViewPanel::getViewportScale()
{
	return m_ViewportScale;
}

void ViewPanel::setClipPanel(FloatRect clipPanel)
{
	m_ClipPanel = clipPanel;
	m_PanelViewport = View(clipPanel);
	m_PanelViewport.setViewport(m_ViewportScale);
}

void ViewPanel::setViewportScale(FloatRect viewportScale)
{
	m_ViewportScale = viewportScale;
	m_PanelViewport.setViewport(m_ViewportScale);
}

void ViewPanel::setViewportDraw(RenderWindow& window)
{
	window.setView(m_PanelViewport);
}
