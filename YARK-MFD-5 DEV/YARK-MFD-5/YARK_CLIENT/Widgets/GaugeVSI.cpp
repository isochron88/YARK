#include "GaugeVSI.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

GaugeVSI::GaugeVSI()
{

}



std::string GaugeVSI::GetTitle()
{
	return "Gauge VSI";
}

void GaugeVSI::Draw(XY pos, XY size) {

	int PLANE_MARKER_HALF_WIDTH = 35;
	int PLANE_MARKER_HALF_HEIGHT = 27;
	int OFFSET_GAP = 7;
	int LENGTH_CROSS_ARM = 40;
	
	draw->SwitchShader(SHADER_2D);
	draw->SetDrawColor2D(0, 0, 0);
	draw->DrawRect2D(pos.x, pos.y, pos.x + size.x, pos.y + size.y);

	VesselPacket VP = client.Vessel;
	float VertSpeed = VP.VVI;

	float xCenter = pos.x + size.x / 2;
	float yCenter = pos.y + size.y / 2;

	//Draw Outer Guage Circle---------------------------------------------------------
	glLineWidth(2);
	draw->BindTex2D(0);
	draw->SetDrawColor2D(0, 1, 0);


	int i = 0;
	int iNumSegment = 100; //number of segments used to draw circle

	float twicePi = 2.0f * glm::pi<float>();
	float radius = 150;

	while (i < iNumSegment)
	{
		float theta = i * twicePi / iNumSegment;
		float xCurr = xCenter + (radius * cos(theta));
		float yCurr = yCenter + (radius * sin(theta));
		i++;
		theta = i * twicePi / iNumSegment;
		float xNext = xCenter + (radius * cos(theta));
		float yNext = yCenter + (radius * sin(theta));
		draw->DrawLine2D(xCurr, yCurr, xNext, yNext);
	}
	//Draw Circle End---------------------------------------------------------------

	//Draw Needle-------------------------------------------------------------------
	DrawCross(5, xCenter, yCenter);
	
	float AngleToRotate = ScaleVertSpeedToDeg(VertSpeed);
	RotateNeedle(AngleToRotate, xCenter, yCenter);

	//Draw Needle End----------------------------------------------------------------

	//Draw Dashed Circle--------------------------------------------------------------
	glLineWidth(2);
	draw->BindTex2D(0);
	draw->SetDrawColor2D(0, 1, 0);
	draw->SetView2D();
	//--------------------------------------------------------------------------------
	int iArcOffsetFromCenter = 65;
	//int iShiftGaugeDown = 25; //so Gauge is not at top of window
	float AngleStart = 190;
	float AngleEnd = 350;
	float DashDistBetweenDashDeg = 8;
	int DashHeightShort = 10;
	int DashHeightLong = 20;

	
	for (float theta = AngleStart; theta <= AngleEnd; theta += DashDistBetweenDashDeg)
	{
		if (((int)theta + 10) % int(DashDistBetweenDashDeg * 5)) //make each nth second dash height longer
			DrawRadialLine(theta, xCenter, yCenter, size, iArcOffsetFromCenter, DashHeightShort);
		else
			DrawRadialLine(theta, xCenter, yCenter, size, iArcOffsetFromCenter, DashHeightLong);	
	}
	//------------------------------------------------------------------------------
	
	DrawRadialLine(150.f, xCenter, yCenter, size, iArcOffsetFromCenter, DashHeightLong); //15 UP 100 
	DrawRadialLine(30.f, xCenter, yCenter, size, iArcOffsetFromCenter, DashHeightLong);	//15 Down 100 
	 
	DrawRadialLine(110.f, xCenter, yCenter, size, iArcOffsetFromCenter, DashHeightLong); //20 UP 100 
	DrawRadialLine(70.f, xCenter, yCenter, size, iArcOffsetFromCenter, DashHeightLong);	//20 Down 100 

	//draw->SetView2D();

	//Draw Dashed Circle End--------------------------------------------------------

	//Draw Card Text----------------------------------------------------------------	

	float RadiusTextCircle = PLANE_MARKER_HALF_WIDTH + OFFSET_GAP + LENGTH_CROSS_ARM + OFFSET_GAP + 3;

	DrawText("0", 270.f, xCenter, yCenter, RadiusTextCircle);
	DrawText("5", 310.f, xCenter, yCenter, RadiusTextCircle);
	DrawText("5", 230.f, xCenter, yCenter, RadiusTextCircle);

	DrawText("10", 190.f, xCenter, yCenter, RadiusTextCircle);
	DrawText("10", 350.f, xCenter, yCenter, RadiusTextCircle);
	
	DrawText("15", 150.f, xCenter, yCenter, RadiusTextCircle);
	DrawText("15", 30.f, xCenter, yCenter, RadiusTextCircle);
	
	DrawText("20", 110.f, xCenter, yCenter, RadiusTextCircle);
	DrawText("20", 70.f, xCenter, yCenter, RadiusTextCircle);
	//Draw Card Text End-------------------------------------------------------------


}

//---------------------------------------------------------------------------------------------------------------------------------
void GaugeVSI::RotateNeedle(float AngleToRotate, float xCenter, float yCenter)
{
	//build rotation matrix
	//1. Start with an identity matrix
	glm::mat4 rotNumberMat = glm::mat4(1.0f);
	//2. Translate the matrix by -centre of the object (make the pivot the origin)
	rotNumberMat = glm::translate(rotNumberMat, glm::vec3(xCenter, yCenter, 0));
	//3.  Rotate the matrix by the desired amount
	rotNumberMat = glm::rotate(rotNumberMat, glm::radians(AngleToRotate), glm::vec3(0, 0, 1));
	//4. Translate the matrix by centre of the object (translate back)
	rotNumberMat = glm::translate(rotNumberMat, -glm::vec3(xCenter, yCenter, 0));
	//5. Use the resulting matrix to transform the object that you desire to rotate
	draw->SetView2D(rotNumberMat);
	glLineWidth(2);
	draw->SetDrawColor2D(0, 1, 0);
	//VSI Needle
	draw->DrawLine2D(xCenter + 0, yCenter + 26, xCenter - 10, yCenter + 9);
	draw->DrawLine2D(xCenter - 10, yCenter + 9, xCenter - 0, yCenter - 120);
	draw->DrawLine2D(xCenter - 0, yCenter - 120, xCenter + 10, yCenter + 9);
	draw->DrawLine2D(xCenter + 10, yCenter + 9, xCenter + 0, yCenter + 26);

	draw->SetViewText();
}
//---------------------------------------------------------------------------------------------------------------------------------
float GaugeVSI::ScaleVertSpeedToDeg(float VertSpeed)
{
	float VertSpeedDeg;
	float ScaledVal;
	int iMaxRange = 45; //range -22.5 to + 22.5
	float HalfRange = (float)iMaxRange / 2; 	
	/*
	<-22.5+->90, -22.5->90, -20->110, -15->150, -10->190, -5->230, 0->270, +5->310, +10->350, +11.25->0, +15->30, +20->70, +22.5->90, >+22.5+->90
	33.75
	<-22.5+->90, -22.5->90, -20->110, -15->150, -10->190, -5->230, 0->270, +5->310, +10->350, +11.25->0, +15->30, +20->70, +22.5->90, >+22.5+->90
	*/	
	
	if(VertSpeed > HalfRange || VertSpeed < -HalfRange)
		return 90;
	ScaledVal = VertSpeed + HalfRange;
	VertSpeedDeg = ((ScaledVal / iMaxRange) * 360)+90;

	if (VertSpeedDeg >= 360)
		VertSpeedDeg = VertSpeedDeg - 360;
	return VertSpeedDeg;

}
//---------------------------------------------------------------------------------------------------------------------------------
void GaugeVSI::DrawRadialLine(float Angle, float xCenter, float yCenter, XY size, int iArcOffsetFromCenter, int iDashHeight)
{
	float y = -glm::cos(glm::radians(Angle));
	float x = glm::sin(glm::radians(Angle));
	float r1 = size.x / 2 - iArcOffsetFromCenter;
	float r2 = size.x / 2 - iArcOffsetFromCenter - iDashHeight;
	draw->DrawLine2D(xCenter + x * r1, yCenter + y * r1, xCenter + x * r2, yCenter + y * r2);
}
//---------------------------------------------------------------------------------------------------------------------------------
void GaugeVSI::DrawText(std::string strTextToRotate, float AngleToRotate, float xCenter, float yCenter, float RadiusTextCircle)
{
	draw->SwitchShader(SHADER_TEXT);
	draw->SetDrawColor2D(0, 1, 0);
	draw->DrawString(f, strTextToRotate, xCenter + RadiusTextCircle * cosf(glm::radians(AngleToRotate - 90.f)) - (f->GetTextWidth(strTextToRotate) / 2),
					 yCenter + RadiusTextCircle * sinf(glm::radians(AngleToRotate - 90.f)));
}
//---------------------------------------------------------------------------------------------------------------------------------
void GaugeVSI::DrawCross(int iArmLength, float xCenter, float yCenter)
{
	glLineWidth(2);
	draw->BindTex2D(0);
	draw->SetDrawColor2D(0, 1, 0);

	draw->DrawLine2D(xCenter - iArmLength, yCenter, xCenter + iArmLength, yCenter);
	draw->DrawLine2D(xCenter, yCenter - iArmLength, xCenter, yCenter + iArmLength);
}
