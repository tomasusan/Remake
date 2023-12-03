#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

UCLASS()
class REMAKE_API AGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	float HalfLineSize = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	float LineThickness = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	FLinearColor LineColor = FLinearColor::Red;

private:
	void DrawCrossHair();
};
