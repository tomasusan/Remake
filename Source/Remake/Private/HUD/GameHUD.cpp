#include "HUD/GameHUD.h"
#include "Engine/Canvas.h"

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
}

void AGameHUD::DrawCrossHair() {
	const int32 SizeX = Canvas->SizeX;
	const int32 SizeY = Canvas->SizeY;
	const TInterval<float> Center(SizeX * 0.5, SizeY * 0.5);
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}


