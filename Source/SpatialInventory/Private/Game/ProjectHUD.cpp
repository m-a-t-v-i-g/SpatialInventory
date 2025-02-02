// Spatial Inventory С++ template by matvig.


#include "Game/ProjectHUD.h"
#include "Engine/Canvas.h"

void AProjectHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrosshair();
}

void AProjectHUD::DrawCrosshair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5, Canvas->SizeY * 0.5);

	const float HalfLineSize = 15.0;
	const float LineThickness = 2.0;
	const FLinearColor LineColor = FLinearColor::White;

	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}