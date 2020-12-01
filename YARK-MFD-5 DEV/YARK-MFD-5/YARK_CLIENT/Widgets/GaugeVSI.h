#pragma once

#include "Widget.h"
#include "../Client/Client.h"
#include "../Wrap/Texture.h"
#include "../Wrap/Window.h"
#include "../Wrap/Draw.h"

class GaugeVSI : public Widget 
{
public:
	std::string GetTitle();
	GaugeVSI();
	void Draw(XY pos, XY size);
	void DrawText(std::string strTextToRotate, float AngleToRotate, float xCenter, float yCenter, float RadiusTextCircle);
	void DrawCross(int iArmLength, float xCenter, float yCenter);
	void DrawRadialLine(float Angle, float xCenter, float yCenter, XY size, int iArcOffsetFromCenter, int iDashHeight);
	float ScaleVertSpeedToDeg(float VertSpeed);
	void RotateNeedle(float AngleToRotate, float xCenter, float yCenter);
};
