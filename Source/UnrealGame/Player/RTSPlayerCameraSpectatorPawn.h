// Niall Maple & Edward Hawksworth - 19/03/2018 ~

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "RTSPlayerCameraSpectatorPawn.generated.h"

/*
*		Class:			RTSPlayerCameraSpectatorPawn
*		Description:	Handles Movement / Rotation / Zoom
*		Created:		19/03/2018
*		Author:			Niall Maple
*/

UCLASS()
class UNREALGAME_API ARTSPlayerCameraSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

	// Functions
public:
	ARTSPlayerCameraSpectatorPawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ZoomInByWheel();
	void ZoomOutByWheel();
	void RotateLeftByWheel();
	void RotateRightByWheel();
	void RotateUpByWheel();
	void RotateDownByWheel();

	// Position and Rotation of Camera
	void RepositionCamera();

	void SprintInput(float direction);
	void RotateInput(float direction);
	void MoveCameraForwardInput(float direction);
	void MoveCameraRightInput(float direction);
	void MoveCameraUpInput(float direction);
	void ZoomCameraInInput(float direction);

	float GetLandTerrainSurfaceAtCoord(float XCoord, float YCoord) const;

protected:
	virtual void BeginPlay() override;

private:
	FVector MoveCameraForward(float direction);
	FVector MoveCameraRight(float direction);
	FRotator GetIsolatedCameraYaw();
	float MoveCameraUp(float direction);
	void ZoomCameraIn(float direction);
	void TurnCameraUp(float direction);
	void TurnCameraRight(float direction);

	// Variables
private:
	float m_fSprintMod;
	float m_fRotateMod;
	float m_fMoveForwardMod;
	float m_fMoveRightMod;
	float m_fMoveUpMod;
	float m_fZoomInMod;

public:	

	/** Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "C++ Camera")
		class UCameraComponent* m_pCamera;
	/** Camera XY Limits */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		float m_fCameraXYLimit;
	/** Camera Height Over Terrain*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		float m_fCameraHeight;
	/** Camera Max Height Over Terrain */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		float m_fCameraMaxHeight;
	/** Camera Min Height Over Terrain */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		float m_fCameraMinHeight;
	/** Camera Rotation Around Z Axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		float m_fCameraZAngle;
	/** Camera Height Angle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		float m_fCameraHeightAngle;
	/** Camera Pitch Angle Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		float m_fCameraHeightAngleMax;
	/** Camera Pitch Angle Min */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		float m_fCameraHeightAngleMin;
	/** Camera Radius (Distance From Pawn Position) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		float m_fCameraRadius;
	/** Camera Radius Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		float m_fCameraRadiusMax;
	/** Camera Radius Min */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		float m_fCameraRadiusMin;
	/** Camera Zoom Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		float m_fCameraZoomSpeed;
	/** Camera Rotation Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		float m_fCameraRotationSpeed;
	/** Camera Movement Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		float m_fCameraMovementSpeed;
	/** Camera Scroll Boundary */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		float m_fCameraScrollBoundary;
	/** Is The Camera Disabled */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Camera")
		bool m_bCanMoveCamera;
	
	
};
