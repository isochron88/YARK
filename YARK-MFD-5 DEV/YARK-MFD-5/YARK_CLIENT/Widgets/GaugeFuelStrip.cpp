#include "GaugeFuelStrip.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

GaugeFuelStrip::GaugeFuelStrip()
{

}



std::string GaugeFuelStrip::GetTitle()
{
	return "Gauge Fuel Strip";
}

void GaugeFuelStrip::Draw(XY pos, XY size) 
{
	VesselPacket VP = client.Vessel;
	
	float FuelLiquidFull = VP.LiquidFuelTot;
	//float FuelLiquidHave = VP.LiquidFuel; not used
	float FuelLiquidHaveStage = VP.LiquidFuelS;
	
	float xCenter = pos.x + size.x / 2;
	float yCenter = pos.y + size.y / 2;
	
	int iShiftGaugeDown = 50;
	
	int iDistBetweenDash = 6;
	int iNthDashLonger = 5; //make every nth second dash height longer
	int iDashCnt = 50;		//CHANGE TO total number of dashes
	int iDashHeightShort = 10;
	int iDashHeightLong = 20;
	int iPositionStart = iShiftGaugeDown;
	int iPositionEnd = iPositionStart + (iDistBetweenDash * iDashCnt);
	int iOffsetFromCenter = 40;
	
	int iPositionCurrentOffset = iPositionStart - (iDistBetweenDash * iNthDashLonger); // required to make longer dashes start from first drawn dash
	
	glLineWidth(2);
	draw->SwitchShader(SHADER_2D);
	draw->SetDrawColor2D(0, 1, 0);
	//Draw LH Gauge Dashes-----------------------------------------------------------
	for (int iPositionCurrent = iPositionStart; iPositionCurrent <= iPositionEnd; iPositionCurrent += iDistBetweenDash)
	{
		if ((iPositionCurrent - iPositionCurrentOffset) % (iDistBetweenDash * iNthDashLonger)) //make each nth second dash height longer
		{
			draw->DrawLine2D(xCenter + iDashHeightShort - iOffsetFromCenter, iPositionCurrent, xCenter - iOffsetFromCenter, iPositionCurrent);
		}
		else
		{
			draw->DrawLine2D(xCenter + iDashHeightLong - iOffsetFromCenter, iPositionCurrent, xCenter - iOffsetFromCenter, iPositionCurrent);
		}
	}
	//Draw LH Gauge Dashes End------------------------------------------------------
	//Draw RH Gauge Dashes-----------------------------------------------------------
	for (int iPositionCurrent = iPositionStart; iPositionCurrent <= iPositionEnd; iPositionCurrent += iDistBetweenDash)
	{
		if ((iPositionCurrent- iPositionCurrentOffset) % (iDistBetweenDash * iNthDashLonger)) //make each nth second dash height longer
		{
			draw->DrawLine2D(xCenter + iOffsetFromCenter - iDashHeightShort, iPositionCurrent, xCenter + iOffsetFromCenter, iPositionCurrent);
		}
		else
		{
			draw->DrawLine2D(xCenter + iOffsetFromCenter - iDashHeightLong, iPositionCurrent, xCenter + iOffsetFromCenter, iPositionCurrent);
		}
	}
	//Draw RH Gauge Dashes End------------------------------------------------------
	//Draw Gauge Numbers----------------------------------------------------------------	
	draw->SwitchShader(SHADER_TEXT);
	draw->SetDrawColor2D(0, 1, 0);

	bool bAscendingStrip = false; // numbers are normally descending for a fuel guage i.e. 100% at top
	
	int iNumberFirst = 0;
	int iNumberFinal = 100;
	int iNumberIncrement = 10;
	int iPositionCurrentNumber = iShiftGaugeDown;
	
	
	for (int iNumberCurrent = iNumberFirst; iNumberCurrent <= iNumberFinal; iNumberCurrent += iNumberIncrement)
	{
		int yPositionText = iPositionCurrentNumber + (f->size / 2) - 2;
		if (bAscendingStrip == false) //if numbers are descending
		{
			int iPositionFinal = iShiftGaugeDown + (iDistBetweenDash * iDashCnt) + iDashCnt;
			yPositionText = iPositionFinal - iPositionCurrentNumber + (f->size / 2) - 2;
		}
		draw->DrawString(f, std::to_string(iNumberCurrent), xCenter - (f->GetTextWidth(std::to_string(iNumberCurrent)) / 2), yPositionText);
		iPositionCurrentNumber += iNthDashLonger * iDistBetweenDash;
	}
	//Draw Gauge Numbers End------------------------------------------------------------
	float yValue = ScaleValueToGraphLocation(bAscendingStrip, iShiftGaugeDown, iDistBetweenDash, iDashCnt, FuelLiquidFull, FuelLiquidHaveStage);
	DrawIndicatorArrows(iOffsetFromCenter + 3, 15, xCenter, yValue);
}
//---------------------------------------------------------------------------------------------------------------------------------
void GaugeFuelStrip::DrawIndicatorArrows(int iOffsetFromCenter, int iSideLength, float xCenter, float yValue)
{
	glLineWidth(2);
	draw->SwitchShader(SHADER_2D);
	draw->SetDrawColor2D(0, 1, 0);
	//LH Indicator Arrow
	draw->DrawLine2D(xCenter - iOffsetFromCenter, yValue, xCenter - iOffsetFromCenter - iSideLength * sqrtf(3/2), yValue - (iSideLength/2));
	draw->DrawLine2D(xCenter - iOffsetFromCenter - iSideLength * sqrtf(3 / 2), yValue - (iSideLength / 2), 
		xCenter - iOffsetFromCenter - iSideLength * sqrtf(3 / 2), yValue + (iSideLength / 2));
	draw->DrawLine2D(xCenter - iOffsetFromCenter - iSideLength * sqrtf(3 / 2), yValue + (iSideLength / 2), xCenter - iOffsetFromCenter, yValue);
	//RH Indicator Arrow
	draw->DrawLine2D(xCenter + iOffsetFromCenter, yValue, xCenter + iOffsetFromCenter + iSideLength * sqrtf(3 / 2), yValue - (iSideLength / 2));
	draw->DrawLine2D(xCenter + iOffsetFromCenter + iSideLength * sqrtf(3 / 2), yValue - (iSideLength / 2),
		xCenter + iOffsetFromCenter + iSideLength * sqrtf(3 / 2), yValue + (iSideLength / 2));
	draw->DrawLine2D(xCenter + iOffsetFromCenter + iSideLength * sqrtf(3 / 2), yValue + (iSideLength / 2), xCenter + iOffsetFromCenter, yValue);
}
//---------------------------------------------------------------------------------------------------------------------------------
float GaugeFuelStrip::ScaleValueToGraphLocation(bool bAscendingStrip, int iOffsetShiftGaugeDown, int iDistBetweenDash, int iDashCnt, float FuelLiquidFull, float FuelLiquidHaveStage)
{
	float yGraphLocation = 0;
	float ValueScaled = (FuelLiquidHaveStage / FuelLiquidFull) * (iDistBetweenDash * iDashCnt);
	if (FuelLiquidHaveStage != -1)
	{
		yGraphLocation = iOffsetShiftGaugeDown + ValueScaled;
		if (bAscendingStrip == false) //if numbers are descending
		{
			int iPositionFinal = iOffsetShiftGaugeDown + (iDistBetweenDash * iDashCnt) + iDashCnt;
			yGraphLocation = iPositionFinal - (iOffsetShiftGaugeDown + ValueScaled);
		}
	}	
	return yGraphLocation;
}
//---------------------------------------------------------------------------------------------------------------------------------