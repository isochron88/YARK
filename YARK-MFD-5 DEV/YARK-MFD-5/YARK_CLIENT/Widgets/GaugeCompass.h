#pragma once

#include "Widget.h"
#include "../Client/Client.h"
#include "../Wrap/Texture.h"
#include "../Wrap/Window.h"
#include "../Wrap/Draw.h"

class GaugeCompass : public Widget 
{
	glm::mat4 rotCompassCardMat;
public:
	std::string GetTitle();
	GaugeCompass();
	void Draw(XY pos, XY size);
	void RotateText(std::string strTextToRotate, float AngleToRotate, float xCenter, float yCenter, float RadiusTextCircle);
};
