#pragma once

#include "Widget.h"
#include "../Client/Client.h"
#include "../Wrap/Texture.h"
#include "../Wrap/Window.h"
#include "../Wrap/Draw.h"

class NavGauge : public Widget {
	//GLuint chevronTex, triTex, tri_90;
	GLuint NavGaugeTex;
	GLuint NavGaugeBezelTex;
	GLuint NavGaugeCompassCardTex;
	//GLuint shader, proj, rotUnif;
public:
	std::string GetTitle();
	NavGauge();
	void Draw(XY pos, XY size);
};
