// Niall Maple & Edward Hawksworth - 19/03/2018 ~

#include "RTSPlayerController.h"
#include "UnrealGame/HUD/RTSHud.h"

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
}

void ARTSPlayerController::MoveReleased()
{
}