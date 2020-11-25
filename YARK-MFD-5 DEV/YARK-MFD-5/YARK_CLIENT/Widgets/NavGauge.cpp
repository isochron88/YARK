#include "NavGauge.h"

//#include "NavBall.h"
#include <iostream>

NavGauge::NavGauge() {
	/*chevronTex = loadTexture("Tex/ai/chevron.png");
	triTex = loadTexture("Tex/ai/triangle.png");
	tri_90 = loadTexture("Tex/ai/tri_90.png");*/
	NavGaugeTex = loadTexture("Tex/nav_gauge.png", false);
	NavGaugeBezelTex = loadTexture("Tex/nav_gauge_v13bezel.png", false);
	NavGaugeCompassCardTex = loadTexture("Tex/nav_gauge_v13compasscard.png", false);
	//memset((char*)&oldVessel, 0, sizeof(VesselPacket));
}

//#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtc/matrix_transform.hpp"

#define XSPACE 35
#define YSPACE 8
#define XINSET 5

#define TEX_Y_OFFSET 6
#define DOWN_SHIFT 5

std::string NavGauge::GetTitle() {
	return "Nav Gauge";
}

void NavGauge::Draw(XY pos, XY size) {

	//Draw the compass card (and bearing pointer)
	//draw->SwitchShader(SHADER_2D);
	//draw->SetDrawColor2D(0, 0, 0);
	//draw->DrawRect2D(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
	//Determine vessel heading
	VesselPacket VP = client.Vessel;

	// Rotate and draw compass card	
	draw->SwitchShader(SHADER_2D);
	draw->SetDrawColor2D(1, 1, 1); //White
	draw->BindTex2D(NavGaugeCompassCardTex);

	//build rotation matrix
	//1. Start with an identity matrix
	glm::mat4 rotMat = glm::mat4(1.0f);
	//2. Translate the matrix by -centre of the object (make the pivot the origin)
	rotMat = glm::translate(rotMat, glm::vec3(pos.x + (390 / 2) + 2, pos.y + 390 / 2, 0));
	//3.  Rotate the matrix by the desired amount
	rotMat = glm::rotate(rotMat, glm::radians(-VP.Heading), glm::vec3(0, 0, 1));
	//4. Translate the matrix by centre of the object (translate back)
	rotMat = glm::translate(rotMat, -glm::vec3(pos.x + (390 / 2) + 2, pos.y + 390 / 2, 0));
	//5. Use the resulting matrix to transform the object that you desire to rotate
	draw->SetView2D(rotMat);
	draw->DrawRect2D(pos.x, pos.y, pos.x + 390, pos.y + 390); //390x390 size of image
	draw->SetView2D(); //call this to prevent remaining textures being translated



// Draw Bezel
	draw->SwitchShader(SHADER_2D);
	draw->SetDrawColor2D(1, 1, 1); //White
	draw->BindTex2D(NavGaugeBezelTex);
	draw->DrawRect2D(pos.x, pos.y, pos.x + 390, pos.y + 390); //390x390 size of image
	
	//GUI.matrix = Matrix4x4.identity;    //Reset rotation matrix
	//drawPointer(heading);
	//draw the OFF flag if necessary
	//if (SteamShip.NavHeading == -1 && SteamShip.NavDist == -1)
	//	GUI.DrawTextureWithTexCoords(new Rect(56 * Scale, 127 * Scale, 50 * Scale, 21 * Scale), texture, new Rect(0.8012f, 0.4287f, 0.0625f, 0.0258f));
	
}
