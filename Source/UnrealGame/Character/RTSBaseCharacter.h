// Niall Maple & Edward Hawksworth - 19/03/2018 ~

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RTSBaseCharacter.generated.h"

UCLASS()
class UNREALGAME_API ARTSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	class UMaterialInstanceDynamic* m_pInitialMaterial;
public:
	
	UPROPERTY(EditAnywhere, Category = "C++ AI")
		class UBehaviorTree* m_pBehaviourTree;

public:
	// Sets default values for this character's properties
	ARTSBaseCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetSelected();

	void SetDeselected();
	
};
