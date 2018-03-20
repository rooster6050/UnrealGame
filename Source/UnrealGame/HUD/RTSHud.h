// Niall Maple & Edward Hawksworth - 19/03/2018 ~

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHud.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGAME_API ARTSHud : public AHUD
{
	GENERATED_BODY()
	
private:
	TArray<class ARTSBaseCharacter*> m_pFoundUnits;
private:
	void RenderLine(FVector2D start, FVector2D end);
	void HandleSelection();

public:
	FVector2D m_vInitialPoint;
	FVector2D m_vCurrentPoint;

public:
	FVector2D GetMousePos2D();

	uint8 m_bStartSelecting : 1;

	virtual void DrawHUD() override; // Basically Tick
	
	
};
