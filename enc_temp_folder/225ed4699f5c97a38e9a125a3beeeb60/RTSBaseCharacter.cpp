// Niall Maple & Edward Hawksworth - 19/03/2018 ~

#include "RTSBaseCharacter.h"
#include "Classes/Materials/MaterialInstanceDynamic.h"
#include "Classes/Components/SkeletalMeshComponent.h"

// Sets default values
ARTSBaseCharacter::ARTSBaseCharacter() :
	m_pInitialMaterial(NULL)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARTSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (USkeletalMeshComponent* pMesh = GetMesh())
	{
		if(UMaterialInterface* pParentMaterial = pMesh->GetMaterial(0))
		{
			m_pInitialMaterial = UMaterialInstanceDynamic::Create(pParentMaterial, this);
		}
	}
	
}

// Called every frame
void ARTSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARTSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARTSBaseCharacter::SetSelected()
{
	if (m_pInitialMaterial)
	{
		FName paramName("BodyColour");
		FLinearColor selectedColour(0.0f, 1.0f, 0.0f);
		m_pInitialMaterial->SetVectorParameterValue(paramName, selectedColour);
	}
}

void ARTSBaseCharacter::SetDeselected()
{
	if (m_pInitialMaterial)
	{
		FName paramName("BodyColour");
		FLinearColor selectedColour;
		FMaterialParameterInfo info;
		info.Name = paramName;
		m_pInitialMaterial->GetVectorParameterDefaultValue(info, selectedColour);
		m_pInitialMaterial->SetVectorParameterValue(paramName, selectedColour);
	}
}
