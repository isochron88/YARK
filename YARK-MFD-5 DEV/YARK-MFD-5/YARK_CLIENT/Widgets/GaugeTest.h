#pragma once

#include "Widget.h"
#include "../Client/Client.h"
#include "../Wrap/Texture.h"
#include "../Wrap/Window.h"
#include "../Wrap/Draw.h"

class GaugeTest : public Widget {
	GLuint chevronTex, triTex, tri_90;
public:
	std::string GetTitle();
	GaugeTest();
	void Draw(XY pos, XY size);
	void RotateText(std::string strTextToRotate, float AngleToRotate, float xCenter, float yCenter, float RadiusTextCircle);
};
