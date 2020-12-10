#pragma once

#include "Widget.h"
#include "../Client/Client.h"
#include "../Wrap/Texture.h"
#include "../Wrap/Window.h"
#include "../Wrap/Draw.h"

class GaugeFuelStrip : public Widget 
{
public:
	std::string GetTitle();
	GaugeFuelStrip();
	void Draw(XY pos, XY size);
	void DrawIndicatorArrows(int iOffsetFromCenter, int iSideLength, float xCenter, float yValue);
	//float ScaleValueToGraphLocation(int iShiftGaugeDown, float value);
	float ScaleValueToGraphLocation(bool bAscendingStrip, int iShiftGaugeDown, int iDistBetweenDash, int iDashCnt, float FuelLiquidFull, float FuelLiquidHaveStage);
};
