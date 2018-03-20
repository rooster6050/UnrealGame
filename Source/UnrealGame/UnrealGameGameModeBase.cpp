// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealGameGameModeBase.h"
#include "UnrealGame/Player/RTSPlayerController.h"
#include "UnrealGame/Player/RTSPawn.h"
#include "UnrealGame/Player/RTSPlayerCameraSpectatorPawn.h"
#include "UnrealGame/HUD/RTSHud.h"

AUnrealGameGameModeBase::AUnrealGameGameModeBase()
{
	PlayerControllerClass = ARTSPlayerController::StaticClass();
	DefaultPawnClass = ARTSPlayerCameraSpectatorPawn::StaticClass();
	HUDClass = ARTSHud::StaticClass();
}
