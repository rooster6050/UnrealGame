// Niall Maple & Edward Hawksworth - 19/03/2018 ~

#include "RTSPlayerCameraSpectatorPawn.h"


// Sets default values
ARTSPlayerCameraSpectatorPawn::ARTSPlayerCameraSpectatorPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARTSPlayerCameraSpectatorPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTSPlayerCameraSpectatorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARTSPlayerCameraSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

