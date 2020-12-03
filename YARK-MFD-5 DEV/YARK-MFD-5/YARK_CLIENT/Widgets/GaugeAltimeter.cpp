#include "GaugeAltimeter.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

GaugeAltimeter::GaugeAltimeter()
{

}



std::string GaugeAltimeter::GetTitle()
{
	return "Gauge Altimeter";
}

void GaugeAltimeter::Draw(XY pos, XY size) {

	int PLANE_MARKER_HALF_WIDTH = 35;
	int PLANE_MARKER_HALF_HEIGHT = 27;
	int OFFSET_GAP = 7;
	int LENGTH_CROSS_ARM = 40;
	
	draw->SwitchShader(SHADER_2D);
	draw->SetDrawColor2D(0, 0, 0);
	draw->DrawRect2D(pos.x, pos.y, pos.x + size.x, pos.y + size.y);

	VesselPacket VP = client.Vessel;
	float Altitude = VP.Alt;


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
	
	float AngleToRotateHundreds = ScaleAltitudeComponentToDeg(Altitude, 1000);
	float AngleToRotateThousands = ScaleAltitudeComponentToDeg(Altitude, 10000);
	float AngleToRotateTenThousands = ScaleAltitudeComponentToDeg(Altitude, 100000);
	
	RotateNeedleHundreds(AngleToRotateHundreds, xCenter, yCenter);
	RotateNeedleThousands(AngleToRotateThousands, xCenter, yCenter);
	RotateNeedleTenThousands(AngleToRotateTenThousands, xCenter, yCenter);
	//Draw Needle End----------------------------------------------------------------

	//Draw Dashed Circle--------------------------------------------------------------
	glLineWidth(2);
	draw->BindTex2D(0);
	draw->SetDrawColor2D(0, 1, 0);
	draw->SetView2D();
	//--------------------------------------------------------------------------------
	int iArcOffsetFromCenter = 65;
	//int iShiftGaugeDown = 25; //so Gauge is not at top of window
	float AngleStart = -180;
	float AngleEnd = 180;
	float DashDistBetweenDashDeg = 7.2;
	int DashHeightShort = 10;
	int DashHeightLong = 20;
	
	for (float theta = AngleStart; theta <= AngleEnd; theta += DashDistBetweenDashDeg)
	{
		if ((int)round(theta) % int(DashDistBetweenDashDeg * 5)) //make each nth second dash height longer
		{
			DrawRadialLine(theta, xCenter, yCenter, size, iArcOffsetFromCenter, DashHeightShort);
		}
		else
		{
			DrawRadialLine(theta, xCenter, yCenter, size, iArcOffsetFromCenter, DashHeightLong);
		}
	}

	//Draw Dashed Circle End--------------------------------------------------------

	//Draw Card Text----------------------------------------------------------------	
	float RadiusTextCircle = PLANE_MARKER_HALF_WIDTH + OFFSET_GAP + LENGTH_CROSS_ARM + OFFSET_GAP + 3;
	for (int i = 0; i < 10; i++)
	{
		DrawText(std::to_string(i), (float)i*36, xCenter, yCenter, RadiusTextCircle);
	}
	//Draw Card Text End-------------------------------------------------------------


}

//---------------------------------------------------------------------------------------------------------------------------------
void GaugeAltimeter::RotateNeedleHundreds(float AngleToRotate, float xCenter, float yCenter)
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
	//Needle
	draw->DrawLine2D(xCenter - 5, yCenter + 9, xCenter -5, yCenter - 115);
	draw->DrawLine2D(xCenter - 5, yCenter - 115, xCenter + 0, yCenter - 120);
	draw->DrawLine2D(xCenter + 0, yCenter - 120, xCenter + 5, yCenter - 115);
	draw->DrawLine2D(xCenter + 5, yCenter - 115, xCenter + 5, yCenter + 9);
	draw->DrawLine2D(xCenter + 5, yCenter + 9, xCenter - 5, yCenter + 9);

	draw->SetViewText();
}
//---------------------------------------------------------------------------------------------------------------------------------
void GaugeAltimeter::RotateNeedleTenThousands(float AngleToRotate, float xCenter, float yCenter)
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
	//Altimeter Ten Thousands Needle
	draw->DrawLine2D(xCenter - 2, yCenter + 9, xCenter - 2, yCenter - 120);
	draw->DrawLine2D(xCenter - 2, yCenter - 120, xCenter - 9, yCenter - 130);
	draw->DrawLine2D(xCenter - 9, yCenter - 130, xCenter + 9, yCenter - 130);
	draw->DrawLine2D(xCenter + 9, yCenter - 130, xCenter + 2, yCenter - 120);
	draw->DrawLine2D(xCenter + 2, yCenter - 120, xCenter + 2, yCenter + 9);
	draw->DrawLine2D(xCenter + 2, yCenter + 9, xCenter - 2, yCenter + 9);
	draw->SetViewText();
}
//---------------------------------------------------------------------------------------------------------------------------------
void GaugeAltimeter::RotateNeedleThousands(float AngleToRotate, float xCenter, float yCenter)
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
	//Altimeter Thousands Needle
	draw->DrawLine2D(xCenter - 6, yCenter + 9, xCenter - 6, yCenter - 30);
	draw->DrawLine2D(xCenter - 6, yCenter - 30, xCenter - 14, yCenter - 60);
	draw->DrawLine2D(xCenter - 14, yCenter - 60, xCenter + 0, yCenter - 90);
	draw->DrawLine2D(xCenter + 0, yCenter - 90, xCenter + 14, yCenter - 60);
	draw->DrawLine2D(xCenter + 14, yCenter - 60, xCenter + 6, yCenter - 30);
	draw->DrawLine2D(xCenter + 6, yCenter - 30, xCenter + 6, yCenter + 9);
	draw->DrawLine2D(xCenter + 6, yCenter + 9, xCenter - 6, yCenter + 9);
	draw->SetViewText();
}

//---------------------------------------------------------------------------------------------------------------------------------
float GaugeAltimeter::ScaleAltitudeComponentToDeg(float altitude, int iDivisor)
{
	//Hundreds Divisor is 1000
	//Thousands  Divisor is 10000 
	//Ten Thousands Divisor is 100000  
	int altitudeComponent = (int)altitude % iDivisor;
	float altitudeComponentDeg = ((float)altitudeComponent) / iDivisor * 360;
	return altitudeComponentDeg;

}
//---------------------------------------------------------------------------------------------------------------------------------
void GaugeAltimeter::DrawRadialLine(float Angle, float xCenter, float yCenter, XY size, int iArcOffsetFromCenter, int iDashHeight)
{
	float xSizeGuage = 394; // temporary solution to make radial lines non-scalable
	float y = -glm::cos(glm::radians(Angle));
	float x = glm::sin(glm::radians(Angle));
	//float r1 = size.x / 2 - iArcOffsetFromCenter;
	//float r2 = size.x / 2 - iArcOffsetFromCenter - iDashHeight;
	float r1 = xSizeGuage / 2 - iArcOffsetFromCenter;
	float r2 = xSizeGuage / 2 - iArcOffsetFromCenter - iDashHeight;
	draw->DrawLine2D(xCenter + x * r1, yCenter + y * r1, xCenter + x * r2, yCenter + y * r2);
}
//---------------------------------------------------------------------------------------------------------------------------------
void GaugeAltimeter::DrawText(std::string strTextToRotate, float AngleToRotate, float xCenter, float yCenter, float RadiusTextCircle)
{
	draw->SwitchShader(SHADER_TEXT);
	draw->SetDrawColor2D(0, 1, 0);
	draw->DrawString(f, strTextToRotate, xCenter + RadiusTextCircle * cosf(glm::radians(AngleToRotate - 90.f)) - (f->GetTextWidth(strTextToRotate) / 2),
					 yCenter + RadiusTextCircle * sinf(glm::radians(AngleToRotate - 90.f)));
}
//---------------------------------------------------------------------------------------------------------------------------------
void GaugeAltimeter::DrawCross(int iArmLength, float xCenter, float yCenter)
{
	glLineWidth(2);
	draw->BindTex2D(0);
	draw->SetDrawColor2D(0, 1, 0);

	draw->DrawLine2D(xCenter - iArmLength, yCenter, xCenter + iArmLength, yCenter);
	draw->DrawLine2D(xCenter, yCenter - iArmLength, xCenter, yCenter + iArmLength);
}
