#pragma once

#include "Widget.h"
#include "../Client/Client.h"
#include "../Wrap/Texture.h"
#include "../Wrap/Window.h"
#include "../Wrap/Draw.h"

class GaugeAltimeter : public Widget 
{
public:
	std::string GetTitle();
	GaugeAltimeter();
	void Draw(XY pos, XY size);
	void DrawText(std::string strTextToRotate, float AngleToRotate, float xCenter, float yCenter, float RadiusTextCircle);
	void DrawCross(int iArmLength, float xCenter, float yCenter);
	void DrawRadialLine(float Angle, float xCenter, float yCenter, XY size, int iArcOffsetFromCenter, int iDashHeight);
	float ScaleAltitudeComponentToDeg(float altitude, int iDivisor);
	void RotateNeedleHundreds(float AngleToRotate, float xCenter, float yCenter);
	void RotateNeedleTenThousands(float AngleToRotate, float xCenter, float yCenter);
	void RotateNeedleThousands(float AngleToRotate, float xCenter, float yCenter);
};
