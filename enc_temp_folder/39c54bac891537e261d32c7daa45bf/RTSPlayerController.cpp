// Niall Maple & Edward Hawksworth - 19/03/2018 ~

#include "RTSPlayerController.h"
#include "UnrealGame/HUD/RTSHud.h"
#include "UnrealGame/Character/RTSBaseCharacter.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"
#include "UnrealGame/Character/RTSBaseAICharacterController.h"
#include "DrawDebugHelpers.h"

ARTSPlayerController::ARTSPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;

	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ARTSPlayerController::BeginPlay()
{
	m_pHud = Cast<ARTSHud>(this->GetHUD());
}

void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LMB", IE_Pressed, this, &ARTSPlayerController::SelectionPressed);
	InputComponent->BindAction("LMB", IE_Released, this, &ARTSPlayerController::SelectionReleased);

	//InputComponent->BindAction("RMB", IE_Pressed, this, &ARTSPlayerController::SelectionPressed);
	InputComponent->BindAction("RMB", IE_Released, this, &ARTSPlayerController::MoveReleased);
}

void ARTSPlayerController::SelectionPressed()
{
	m_pHud->m_vInitialPoint = m_pHud->GetMousePos2D();
	m_pHud->m_bStartSelecting = true;
}

void ARTSPlayerController::SelectionReleased()
{
	m_pHud->m_bStartSelecting = false;
	m_pSelectedUnits = m_pHud->GetFoundActors();
}

void ARTSPlayerController::MoveReleased()
{
	if (m_pSelectedUnits.Num() > 0)
	{
		FHitResult hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit);
		for (int i = 0; i < m_pSelectedUnits.Num(); ++i)
		{
			if (AController* pController = m_pSelectedUnits[i]->GetController())
			{
				FVector vMoveLoc = hit.Location + FVector(i / 2 * 100.0f, i % 2 * 100.0f, 0.0f); // Weird offset to prevent clumping - aka GRID formation
				if (ARTSBaseAICharacterController* pUnitController = Cast<ARTSBaseAICharacterController>(pController))
				{
					pUnitController->m_bMoveCommandIssued = true;
					pUnitController->m_vMoveLocation = vMoveLoc;
				}

				// Replacing with Blackboard and Behaviour Tree system
				//UNavigationSystem::SimpleMoveToLocation(pController, vMoveLoc);

				// Debugging
				//if (const UWorld* pWorld = GetWorld())
				//{
				//	float fRadius = 0.25f;
				//	int32 iSegments = 10;
				//	bool bPersist = false;
				//	float fLifeTime = 3.0f;
				//	DrawDebugSphere(pWorld, vMoveLoc, fRadius, iSegments, FColor::Red, bPersist, fLifeTime);
				//}
			}
		}
	}
}