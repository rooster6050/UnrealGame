// Niall Maple & Edward Hawksworth - 19/03/2018 ~

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGAME_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	UFUNCTION()
		void SelectionPressed();

	UFUNCTION()
		void SelectionReleased();

	UFUNCTION()
		void MoveReleased();

	class ARTSHud* m_pHud;

	TArray<class ARTSBaseCharacter*> m_pSelectedUnits;

public:
	ARTSPlayerController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
	
};
