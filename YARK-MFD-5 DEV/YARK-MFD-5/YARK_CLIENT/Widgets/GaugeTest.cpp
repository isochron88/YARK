#include "GaugeTest.h"

//#include "NavBall.h"
#include <iostream>

GaugeTest::GaugeTest() {
	chevronTex = loadTexture("Tex/ai/chevron.png");
	triTex = loadTexture("Tex/ai/triangle.png");
	tri_90 = loadTexture("Tex/ai/tri_90.png");
}

//#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtc/matrix_transform.hpp"

#define XSPACE 35
#define YSPACE 8
#define XINSET 5

#define TEX_Y_OFFSET 6
#define DOWN_SHIFT 5

std::string GaugeTest::GetTitle() {
	return "Gauge Test";
}

void GaugeTest::Draw(XY pos, XY size) {

	draw->SwitchShader(SHADER_2D);
	draw->SetDrawColor2D(0, 0, 0);
	draw->DrawRect2D(pos.x, pos.y, pos.x + size.x, pos.y + size.y);

	VesselPacket VP = client.Vessel;

	//Draw Circle-----------------------------------------------------------------
	/*glLineWidth(2);
	draw->BindTex2D(0);
	draw->SetDrawColor2D(0, 1, 0);


	int i = 0;
	int iNumSegment = 100; //number of segments used to draw circle

	GLfloat twicePi = 2.0f * glm::pi<float>();
	
	GLfloat xCenter = pos.x + size.x / 2;
	GLfloat yCenter = pos.y + size.y / 2;
	GLfloat radius = 150;
	
	while (i < iNumSegment)
	{
		GLfloat theta = i * twicePi / iNumSegment;
		GLfloat xCurr = xCenter + (radius * cos(theta));
		GLfloat yCurr = yCenter + (radius * sin(theta));
		i++;
		theta = i * twicePi / iNumSegment;
		GLfloat xNext = xCenter + (radius * cos(theta));
		GLfloat yNext = yCenter + (radius * sin(theta));
		draw->DrawLine2D(xCurr, yCurr, xNext, yNext);
	}*/
	//Draw Circle End---------------------------------------------------------------
	//Draw Arc----------------------------------------------------------------------
	/*glLineWidth(2);
	draw->BindTex2D(0);
	draw->SetDrawColor2D(0, 1, 0);


	int i = 0;
	int iNumSegment = 100; //number of segments used to draw circle

	GLfloat twicePi = 2.0f * glm::pi<float>();

	GLfloat xCenter = pos.x + size.x / 2;
	GLfloat yCenter = pos.y + size.y / 2;
	GLfloat radius = 150;
	
	GLfloat AngleStart = 180;
	GLfloat AngleEnd = 360;
	//full circle to correspond to 1 and nothing to correspond to 0
	GLfloat s = (AngleEnd - AngleStart)/360;
	while (i < iNumSegment)
	{
		GLfloat theta = (i * twicePi * s / iNumSegment) + (AngleStart * glm::pi<float>() / 180);
		GLfloat xCurr = xCenter + (radius * cos(theta));
		GLfloat yCurr = yCenter + (radius * sin(theta));
		i++;
		theta = (i * twicePi * s / iNumSegment) + (AngleStart * glm::pi<float>() / 180);
		GLfloat xNext = xCenter + (radius * cos(theta));
		GLfloat yNext = yCenter + (radius * sin(theta));
		draw->DrawLine2D(xCurr, yCurr, xNext, yNext);
	}*/
	//Draw Arc End------------------------------------------------------------------
	//Draw Cross----------------------------------------------------------------------
	/*glLineWidth(2);
	draw->BindTex2D(0);
	draw->SetDrawColor2D(0, 1, 0);

	GLfloat xCenter = pos.x + size.x / 2;
	GLfloat yCenter = pos.y + size.y / 2;
	GLfloat ArmLength = 5;
	
	draw->DrawLine2D(xCenter - ArmLength, yCenter, xCenter + ArmLength, yCenter);
	draw->DrawLine2D(xCenter, yCenter - ArmLength, xCenter, yCenter + ArmLength);*/

	//Draw Cross End------------------------------------------------------------------
	//Draw Dashed Circle--------------------------------------------------------------
	glLineWidth(2);
	draw->BindTex2D(0);
	draw->SetDrawColor2D(0, 1, 0);
	int ARC_OFFSET_FROM_CENTER = 65;
	int SHIFT_GAUGE_DOWN = 25; //so Gauge is not at top of window
	float AngleStart = -180;
	float AngleEnd = 180;
	float DegDistBetweenDash = 5;
	int DashHeightA = 10;
	int DashHeightB = 20;
	
	GLfloat xCenter = pos.x + size.x / 2;
	GLfloat yCenter = pos.y + size.y / 2;

	for (float theta = AngleStart; theta <= AngleEnd; theta += DegDistBetweenDash)
	{
		float y = -glm::cos(glm::radians(theta));
		float x = glm::sin(glm::radians(theta));

		float r1 = size.x / 2 - ARC_OFFSET_FROM_CENTER;
		float r2;
		
		if ((int)theta % int(DegDistBetweenDash*2)) //make every second dash height shorter
		{
			r2 = size.x / 2 - ARC_OFFSET_FROM_CENTER - DashHeightA;
		}
		else 
		{
			r2 = size.x / 2 - ARC_OFFSET_FROM_CENTER - DashHeightB;
		}
		//float y_down = size.x / 2 - ARC_OFFSET_FROM_CENTER + SHIFT_GAUGE_DOWN;
		//draw->DrawLine2D(pos.x + size.x / 2 + x * r1, pos.y + y_down + y * r1, pos.x + size.x / 2 + x * r2, pos.y + y_down + y * r2);
		//draw->DrawLine2D(pos.x + size.x / 2 + x * r1, pos.y + size.y / 2 + y * r1, pos.x + size.x / 2 + x * r2, pos.y + size.y / 2 + y * r2);
		draw->DrawLine2D(xCenter + x * r1, yCenter + y * r1, xCenter + x * r2, yCenter + y * r2);
	}
	//Draw Dashed Circle End--------------------------------------------------------
	//Draw Aeroplane Marker---------------------------------------------------------
	/*(320, 170), (319, 170), (317, 190), (285, 196), (285, 204), (317, 204), (318, 217), (310, 220), (310, 224), (320, 224) 
	* 
	* 
	* (0, -27), (-1, -27), (-3, -7), (-35, -1), (-35, 7), (-3, 7), (-2, 20), (-10, 23), (-10, 27), (0, 27) 
	*/
	glLineWidth(2);
	draw->BindTex2D(0);
	draw->SetDrawColor2D(0, 1, 0);

	//GLfloat xCenter = pos.x + size.x / 2;
	//GLfloat yCenter = pos.y + size.y / 2;
	
	//Aeroplane Marker LHS
	draw->DrawLine2D(xCenter + 0, yCenter - 27, xCenter - 1, yCenter - 27);
	draw->DrawLine2D(xCenter - 1, yCenter - 27, xCenter - 3, yCenter - 7);
	draw->DrawLine2D(xCenter - 3, yCenter - 7, xCenter - 35, yCenter - 1);
	draw->DrawLine2D(xCenter - 35, yCenter - 1, xCenter - 35, yCenter + 7);
	draw->DrawLine2D(xCenter - 35, yCenter + 7, xCenter - 3, yCenter + 7);
	draw->DrawLine2D(xCenter - 3, yCenter + 7, xCenter - 2, yCenter + 20);
	draw->DrawLine2D(xCenter - 2, yCenter + 20, xCenter - 10, yCenter + 23);
	draw->DrawLine2D(xCenter - 10, yCenter + 23, xCenter - 10, yCenter + 27);
	draw->DrawLine2D(xCenter - 10, yCenter + 27, xCenter + 0, yCenter + 27);
	//Aeroplane Marker RHS
	draw->DrawLine2D(xCenter + 0, yCenter - 27, xCenter + 1, yCenter - 27);
	draw->DrawLine2D(xCenter + 1, yCenter - 27, xCenter + 3, yCenter - 7);
	draw->DrawLine2D(xCenter + 3, yCenter - 7, xCenter + 35, yCenter - 1);
	draw->DrawLine2D(xCenter + 35, yCenter - 1, xCenter + 35, yCenter + 7);
	draw->DrawLine2D(xCenter + 35, yCenter + 7, xCenter + 3, yCenter + 7);
	draw->DrawLine2D(xCenter + 3, yCenter + 7, xCenter + 2, yCenter + 20);
	draw->DrawLine2D(xCenter + 2, yCenter + 20, xCenter + 10, yCenter + 23);
	draw->DrawLine2D(xCenter + 10, yCenter + 23, xCenter + 10, yCenter + 27);
	draw->DrawLine2D(xCenter + 10, yCenter + 27, xCenter + 0, yCenter + 27);
	
	//glLineWidth(2);
	//draw->BindTex2D(0);
	//draw->SetDrawColor2D(0, 1, 0);

	//GLfloat xCenter = pos.x + size.x / 2;
	//GLfloat yCenter = pos.y + size.y / 2;
	
	int PLANE_MARKER_HALF_WIDTH = 35;
	int PLANE_MARKER_HALF_HEIGHT = 27;
	int OFFSET_GAP = 7;
	int LENGTH_CROSS_ARM = 40;
	
	draw->DrawLine2D(xCenter - PLANE_MARKER_HALF_WIDTH - OFFSET_GAP, yCenter, xCenter - PLANE_MARKER_HALF_WIDTH - OFFSET_GAP - LENGTH_CROSS_ARM, yCenter);
	draw->DrawLine2D(xCenter + PLANE_MARKER_HALF_WIDTH + OFFSET_GAP, yCenter, xCenter + PLANE_MARKER_HALF_WIDTH + OFFSET_GAP + LENGTH_CROSS_ARM, yCenter);
	draw->DrawLine2D(xCenter, yCenter + PLANE_MARKER_HALF_HEIGHT + OFFSET_GAP, xCenter, yCenter + PLANE_MARKER_HALF_HEIGHT + OFFSET_GAP + LENGTH_CROSS_ARM);
	// Draw Arrow
	draw->DrawLine2D(xCenter - 10, yCenter - PLANE_MARKER_HALF_HEIGHT - OFFSET_GAP, xCenter + 10, yCenter - PLANE_MARKER_HALF_HEIGHT - OFFSET_GAP);
	draw->DrawLine2D(xCenter - 10, yCenter - PLANE_MARKER_HALF_HEIGHT - OFFSET_GAP, xCenter, yCenter - PLANE_MARKER_HALF_HEIGHT - OFFSET_GAP - LENGTH_CROSS_ARM);
	draw->DrawLine2D(xCenter + 10, yCenter - PLANE_MARKER_HALF_HEIGHT - OFFSET_GAP, xCenter, yCenter - PLANE_MARKER_HALF_HEIGHT - OFFSET_GAP - LENGTH_CROSS_ARM);
	
	//Draw Aeroplane Marker End-----------------------------------------------------
	//Draw Card Text----------------------------------------------------------------	
	draw->SwitchShader(SHADER_TEXT);
	draw->SetTextColor(0, 1, 0);
	
	float RadiusTextCircle = PLANE_MARKER_HALF_WIDTH + OFFSET_GAP + LENGTH_CROSS_ARM + OFFSET_GAP + 3;
	
	RotateText("3", 30.f, xCenter, yCenter, RadiusTextCircle);
	RotateText("6", 60.f, xCenter, yCenter, RadiusTextCircle);
	RotateText("E", 90.f, xCenter, yCenter, RadiusTextCircle);
	
	RotateText("12", 120.f, xCenter, yCenter, RadiusTextCircle);
	RotateText("15", 150.f, xCenter, yCenter, RadiusTextCircle);
	RotateText("S",  180.f, xCenter, yCenter, RadiusTextCircle);

	RotateText("21", 210.f, xCenter, yCenter, RadiusTextCircle);
	RotateText("24", 240.f, xCenter, yCenter, RadiusTextCircle);
	RotateText("W",  270.f, xCenter, yCenter, RadiusTextCircle);

	RotateText("30", 300.f, xCenter, yCenter, RadiusTextCircle);
	RotateText("33", 330.f, xCenter, yCenter, RadiusTextCircle);
	RotateText("N",  0.f,   xCenter, yCenter, RadiusTextCircle);
	
	
	//Draw Card Text End------------------------------------------------------------
}
void GaugeTest::RotateText(std::string strTextToRotate, float AngleToRotate, float xCenter, float yCenter, float RadiusTextCircle)
{
	//build rotation matrix
	//1. Start with an identity matrix
	glm::mat4 rotMat = glm::mat4(1.0f);
	//2. Translate the matrix by -centre of the object (make the pivot the origin)
	rotMat = glm::translate(rotMat, glm::vec3(xCenter + RadiusTextCircle * cosf(glm::radians(AngleToRotate - 90.f)),
		yCenter + RadiusTextCircle * sinf(glm::radians(AngleToRotate - 90.f)), 0));
	//3.  Rotate the matrix by the desired amount
	rotMat = glm::rotate(rotMat, glm::radians(AngleToRotate), glm::vec3(0, 0, 1));
	//4. Translate the matrix by centre of the object (translate back)
	rotMat = glm::translate(rotMat, -glm::vec3(xCenter + RadiusTextCircle * cosf(glm::radians(AngleToRotate - 90.f)),
		yCenter + RadiusTextCircle * sinf(glm::radians(AngleToRotate - 90.f)), 0));
	//5. Use the resulting matrix to transform the object that you desire to rotate
	draw->SwitchShader(SHADER_TEXT);
	draw->SetDrawColor2D(0, 1, 0);
	draw->SetViewText(rotMat);
	draw->DrawString(f, strTextToRotate, xCenter + RadiusTextCircle * cosf(glm::radians(AngleToRotate - 90.f)) - (f->GetTextWidth(strTextToRotate) / 2),
					 yCenter + RadiusTextCircle * sinf(glm::radians(AngleToRotate - 90.f)));
	draw->SetViewText();
}
//---------------------------------------------------------------------------------------------------------------------------------
