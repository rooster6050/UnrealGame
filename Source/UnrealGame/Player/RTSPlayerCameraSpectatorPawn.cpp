// Niall Maple & Edward Hawksworth - 19/03/2018 ~

#include "RTSPlayerCameraSpectatorPawn.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/Engine/GameViewportClient.h"
#include "Classes/Engine/World.h"

// Sets default values
ARTSPlayerCameraSpectatorPawn::ARTSPlayerCameraSpectatorPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bAddDefaultMovementBindings = false; // Disable default WASD
	bUseControllerRotationPitch = false; // Overriding these controls too
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	if (USphereComponent* pSphere = GetCollisionComponent())
	{
		pSphere->bGenerateOverlapEvents = false;
		pSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		pSphere->SetCollisionProfileName(TEXT("NoCollision"));
		pSphere->SetSimulatePhysics(false);
	}

	m_fCameraXYLimit = 25000.0f;
	m_fCameraHeight = 1000.0f;
	m_fCameraMinHeight = 300.0f;
	m_fCameraMaxHeight = 500.0f;

	m_fCameraRadius = 2000.0f;
	m_fCameraRadiusMin = 1000.0f;
	m_fCameraRadiusMax = 8000.0f;

	m_fCameraZAngle = 0.0f; // Yaw

	m_fCameraHeightAngle = 30.0f;	// Pitch
	m_fCameraHeightAngleMin = 15.0f;
	m_fCameraHeightAngleMax = 60.0f;

	m_fCameraZoomSpeed = 200.0f;	// Mouse Wheel
	m_fCameraRotationSpeed = 10.0f;
	m_fCameraMovementSpeed = 3000.0f;

	m_fCameraScrollBoundary = 25.0f; // Screen Edge Limit

	m_bCanMoveCamera = true;

	m_pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("RTS Camera C++"));
	m_pCamera->SetupAttachment(RootComponent, NAME_None); // Socket name FNAME
	m_pCamera->bUsePawnControlRotation = false;

	RepositionCamera();
}

// Called when the game starts or when spawned
void ARTSPlayerCameraSpectatorPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ARTSPlayerCameraSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (!PlayerInputComponent) return;

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// action mappings

	// mouse zoom
	PlayerInputComponent->BindAction("ZoomOutByWheel", IE_Pressed, this, &ARTSPlayerCameraSpectatorPawn::ZoomOutByWheel);
	PlayerInputComponent->BindAction("ZoomInByWheel", IE_Pressed, this, &ARTSPlayerCameraSpectatorPawn::ZoomInByWheel);

	// mouse rotate (+Ctrl or +Alt)
	// unnecessary...
	//PlayerInputComponent->BindAction("RotateLeftByWheel", IE_Pressed, this, &ARTSPlayerCameraSpectatorPawn::RotateLeftByWheel);
	//PlayerInputComponent->BindAction("RotateRightByWheel", IE_Pressed, this, &ARTSPlayerCameraSpectatorPawn::RotateRightByWheel);
	// needed...
	PlayerInputComponent->BindAction("RotateUpByWheel", IE_Pressed, this, &ARTSPlayerCameraSpectatorPawn::RotateUpByWheel);
	PlayerInputComponent->BindAction("RotateDownByWheel", IE_Pressed, this, &ARTSPlayerCameraSpectatorPawn::RotateDownByWheel);

	// axis mappings

	// keyboard move (WASD, Home/End)
	PlayerInputComponent->BindAxis("MoveForward", this, &ARTSPlayerCameraSpectatorPawn::MoveCameraForwardInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARTSPlayerCameraSpectatorPawn::MoveCameraRightInput);
	PlayerInputComponent->BindAxis("MoveUp", this, &ARTSPlayerCameraSpectatorPawn::MoveCameraUpInput);
	PlayerInputComponent->BindAxis("ZoomIn", this, &ARTSPlayerCameraSpectatorPawn::ZoomCameraInInput);

	// double speed (WASD +Shift)
	PlayerInputComponent->BindAxis("FastMove", this, &ARTSPlayerCameraSpectatorPawn::SprintInput);
	// yaw and pitch (WASD +Ctrl)
	PlayerInputComponent->BindAxis("Rotate", this, &ARTSPlayerCameraSpectatorPawn::RotateInput);

}

void ARTSPlayerCameraSpectatorPawn::ZoomInByWheel()
{
	if (!m_bCanMoveCamera)    return;

	m_fCameraRadius -= m_fCameraZoomSpeed * m_fSprintMod;
	m_fCameraRadius = FMath::Clamp(m_fCameraRadius, m_fCameraRadiusMin, m_fCameraRadiusMax);

	//RepositionCamera();
}


void ARTSPlayerCameraSpectatorPawn::ZoomOutByWheel()
{
	if (!m_bCanMoveCamera)    return;

	m_fCameraRadius += m_fCameraZoomSpeed * m_fSprintMod;
	m_fCameraRadius = FMath::Clamp(m_fCameraRadius, m_fCameraRadiusMin, m_fCameraRadiusMax);

	//RepositionCamera();
}


void ARTSPlayerCameraSpectatorPawn::RotateLeftByWheel()
{
	if (!m_bCanMoveCamera)    return;

	m_fCameraZAngle -= m_fCameraRotationSpeed * m_fSprintMod;

	//RepositionCamera();
}


void ARTSPlayerCameraSpectatorPawn::RotateRightByWheel()
{
	if (!m_bCanMoveCamera)    return;

	m_fCameraZAngle += m_fCameraRotationSpeed * m_fSprintMod;

	//RepositionCamera();
}


void ARTSPlayerCameraSpectatorPawn::RotateUpByWheel()
{
	if (!m_bCanMoveCamera)    return;

	m_fCameraHeightAngle += m_fCameraRotationSpeed * m_fSprintMod;
	m_fCameraHeightAngle = FMath::Clamp(m_fCameraHeightAngle, m_fCameraHeightAngleMin, m_fCameraHeightAngleMax);

	//RepositionCamera();
}


void ARTSPlayerCameraSpectatorPawn::RotateDownByWheel()
{
	if (!m_bCanMoveCamera)    return;

	m_fCameraHeightAngle -= m_fCameraRotationSpeed * m_fSprintMod;
	m_fCameraHeightAngle = FMath::Clamp(m_fCameraHeightAngle, m_fCameraHeightAngleMin, m_fCameraHeightAngleMax);

	//RepositionCamera();
}

//---------------

void ARTSPlayerCameraSpectatorPawn::RepositionCamera()
{
	if (!m_pCamera)
	{
		return;
	}

	FVector NewLocation(0.0f, 0.0f, 0.0f);
	FRotator NewRotation(0.0f, 0.0f, 0.0f);

	float sinCameraZAngle = FMath::Sin(FMath::DegreesToRadians(m_fCameraZAngle));
	float cosCameraZAngle = FMath::Cos(FMath::DegreesToRadians(m_fCameraZAngle));

	float sinCameraHeightAngle = FMath::Sin(FMath::DegreesToRadians(m_fCameraHeightAngle));
	float cosCameraHeightAngle = FMath::Cos(FMath::DegreesToRadians(m_fCameraHeightAngle));

	NewLocation.X = cosCameraZAngle * cosCameraHeightAngle * m_fCameraRadius;
	NewLocation.Y = sinCameraZAngle * cosCameraHeightAngle * m_fCameraRadius;
	NewLocation.Z = sinCameraHeightAngle * m_fCameraRadius;

	// do not allow camera component to go under ground - not enough alone, actor also needed to be limited
	float TerrainSurfaceZ = GetLandTerrainSurfaceAtCoord(GetActorLocation().X + NewLocation.X, GetActorLocation().Y + NewLocation.Y);
	if (GetActorLocation().Z + NewLocation.Z < TerrainSurfaceZ + m_fCameraHeight)
	{
		NewLocation.Z = TerrainSurfaceZ - GetActorLocation().Z + m_fCameraHeight;
	}

	// new camera location
	m_pCamera->SetRelativeLocation(NewLocation);

	// new camera rotation
	NewRotation = (FVector(0.0f, 0.0f, 0.0f) - NewLocation).Rotation();
	m_pCamera->SetRelativeRotation(NewRotation);
}


//////////////////////////////////////////////////////////////////


void ARTSPlayerCameraSpectatorPawn::SprintInput(float Direction)
{
	if (!m_bCanMoveCamera)    return;

	// left or right does not matter, to set double speed in any direction
	m_fSprintMod = FMath::Abs(Direction) * 2.0f;

	// used as multiplier so must be 1 if not pressed
	if (m_fSprintMod == 0.0f)
	{
		m_fSprintMod = 1.0f;
	}
}


void ARTSPlayerCameraSpectatorPawn::RotateInput(float Direction)
{
	if (!m_bCanMoveCamera)    return;

	// left or right does not matter
	m_fRotateMod = FMath::Abs(Direction);
}


void ARTSPlayerCameraSpectatorPawn::MoveCameraForwardInput(float Direction)
{
	if (!m_bCanMoveCamera)    return;

	m_fMoveForwardMod = Direction;
}


void ARTSPlayerCameraSpectatorPawn::MoveCameraRightInput(float Direction)
{
	if (!m_bCanMoveCamera)    return;

	m_fMoveRightMod = Direction;
}


void ARTSPlayerCameraSpectatorPawn::MoveCameraUpInput(float Direction)
{
	if (!m_bCanMoveCamera)    return;

	m_fMoveUpMod = Direction;
}


void ARTSPlayerCameraSpectatorPawn::ZoomCameraInInput(float Direction)
{
	if (!m_bCanMoveCamera)    return;

	m_fZoomInMod = Direction;
}


//------------------------------------------------------------


FVector ARTSPlayerCameraSpectatorPawn::MoveCameraForward(float Direction)
{
	float MovementValue = Direction * m_fCameraMovementSpeed;
	FVector DeltaMovement = MovementValue * GetIsolatedCameraYaw().Vector();
	//FVector NewLocation = GetActorLocation() + DeltaMovement;
	//SetActorLocation(NewLocation);
	return DeltaMovement;
}


FVector ARTSPlayerCameraSpectatorPawn::MoveCameraRight(float Direction)
{
	float MovementValue = Direction * m_fCameraMovementSpeed;
	FVector DeltaMovement = MovementValue * (FRotator(0.0f, 90.0f, 0.0f) + GetIsolatedCameraYaw()).Vector();
	//FVector NewLocation = GetActorLocation() + DeltaMovement;
	//SetActorLocation(NewLocation);
	return DeltaMovement;
}


FRotator ARTSPlayerCameraSpectatorPawn::GetIsolatedCameraYaw()
{
	// FRotator containing Yaw only
	// This could be wrong
	float fYaw = m_pCamera ? m_pCamera->GetComponentTransform().Rotator().Yaw : 0.0f;
	return FRotator(0.0f, fYaw, 0.0f);
}

//---------------

float ARTSPlayerCameraSpectatorPawn::MoveCameraUp(float Direction)
{
	float MovementValue = Direction * m_fCameraMovementSpeed;
	//FVector DeltaMovement = FVector(0.0f, 0.0f, MovementValue);
	//FVector NewLocation = GetActorLocation() + DeltaMovement;
	//NewLocation.Z = FMath::Clamp(NewLocation.Z, CameraRadiusMin, CameraRadiusMax);
	//SetActorLocation(NewLocation);
	return MovementValue;
}

//---------------

void ARTSPlayerCameraSpectatorPawn::ZoomCameraIn(float Direction)
{
	float MovementValue = Direction * m_fCameraMovementSpeed;
	m_fCameraRadius += MovementValue;
	m_fCameraRadius = FMath::Clamp(m_fCameraRadius, m_fCameraRadiusMin, m_fCameraRadiusMax);

	//RepositionCamera();
}


void ARTSPlayerCameraSpectatorPawn::TurnCameraUp(float Direction)
{
	m_fCameraHeightAngle -= Direction * m_fCameraRotationSpeed * 10.0f;
	m_fCameraHeightAngle = FMath::Clamp(m_fCameraHeightAngle, m_fCameraHeightAngleMin, m_fCameraHeightAngleMax);

	//RepositionCamera();
}


void ARTSPlayerCameraSpectatorPawn::TurnCameraRight(float Direction)
{
	m_fCameraZAngle += Direction * m_fCameraRotationSpeed * 10.0f;

	//RepositionCamera();
}


//////////////////////////////////////////////////////////////////

void ARTSPlayerCameraSpectatorPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// mouse position and screen size
	FVector2D MousePosition;
	FVector2D ViewportSize;

	if (const UWorld* pWorld = GetWorld())
	{
		if (UGameViewportClient* pGameViewport = pWorld->GetGameViewport())
		{
			pGameViewport->GetViewportSize(ViewportSize);

			if (pGameViewport->IsFocused(pGameViewport->Viewport) && pGameViewport->GetMousePosition(MousePosition) && m_bCanMoveCamera)
			{
				if (MousePosition.X < m_fCameraScrollBoundary)
				{
					m_fMoveRightMod = -1.0f;
				}
				else if (ViewportSize.X - MousePosition.X < m_fCameraScrollBoundary)
				{
					m_fMoveRightMod = 1.0f;
				}

				if (MousePosition.Y < m_fCameraScrollBoundary)
				{
					m_fMoveForwardMod = 1.0f;
				}
				else if (ViewportSize.Y - MousePosition.Y < m_fCameraScrollBoundary)
				{
					m_fMoveForwardMod = -1.0f;
				}

				//-------------------
				// tweak camera actor position

				FVector ActualLocation = GetActorLocation();
				FVector ActualMovement = FVector::ZeroVector;

				// horizontal movement
				if (m_fRotateMod == 0.f)
				{
					ActualMovement += MoveCameraForward(m_fMoveForwardMod * m_fSprintMod * DeltaSeconds);
					ActualMovement += MoveCameraRight(m_fMoveRightMod * m_fSprintMod * DeltaSeconds);
				}
				ActualLocation += ActualMovement;

				// vertical movement
				m_fCameraHeight += MoveCameraUp(m_fMoveUpMod * m_fSprintMod * DeltaSeconds);
				m_fCameraHeight = FMath::Clamp(m_fCameraHeight, m_fCameraMinHeight, m_fCameraMaxHeight);

				// adjust actor height to surface
				float TerrainSurfaceZ = GetLandTerrainSurfaceAtCoord(ActualLocation.X, ActualLocation.Y);
				ActualLocation.Z = TerrainSurfaceZ + m_fCameraHeight;

				// limit movement area
				ActualLocation.X = FMath::Clamp(ActualLocation.X, -m_fCameraXYLimit, m_fCameraXYLimit);
				ActualLocation.Y = FMath::Clamp(ActualLocation.Y, -m_fCameraXYLimit, m_fCameraXYLimit);

				// move actor
				SetActorLocation(ActualLocation);

				//-------------------
				// tweak camera component relative transform

				// set rotation parameters
				if (m_fRotateMod != 0.f)
				{
					TurnCameraUp(m_fMoveForwardMod * m_fSprintMod * DeltaSeconds);
					TurnCameraRight(m_fMoveRightMod * m_fSprintMod * DeltaSeconds);
				}

				// set zoom distance
				ZoomCameraIn(m_fZoomInMod * m_fSprintMod * DeltaSeconds);

				// adjust camera component relative location and rotation
				RepositionCamera();

				//-------------------
				// debug

				//DrawDebugSphere(    
				//                    GetWorld(),
				//                    GetCollisionComponent()->GetComponentLocation(),
				//                    GetCollisionComponent()->GetScaledSphereRadius(),
				//                    8,
				//                    FColor::White,
				//                    false,
				//                    -1.f
				//                );

				//-------------------
			}
		}

	}
}


//////////////////////////////////////////////////////////////////


float    ARTSPlayerCameraSpectatorPawn::GetLandTerrainSurfaceAtCoord(float XCoord, float YCoord) const
{
	FCollisionQueryParams TraceParams(FName(TEXT("LandTerrain")), false, this);        // TraceTag (info for debugging), bTraceComplex, AddIgnoredActor
	TraceParams.bFindInitialOverlaps = false;                                        // needed

	FHitResult Hit;

	FVector Start = FVector(XCoord, YCoord, GetActorLocation().Z + m_fCameraRadius);
	FVector End = FVector(XCoord, YCoord, -500.f);

	// ECC_ channels should be set properly !!!
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_WorldStatic, TraceParams);

	if (bHit)
	{
		return Hit.ImpactPoint.Z;    // for shape trace it differs from Location
	}

	return 0.f;        // water level
}

//////////////////////////////////////////////////////////////////
