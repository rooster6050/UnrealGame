// Niall Maple & Edward Hawksworth - 19/03/2018 ~

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RTSBaseAICharacterController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGAME_API ARTSBaseAICharacterController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(transient)
		class UBlackboardComponent* m_pBlackboard;
	
	UPROPERTY(transient)
		class UBehaviorTreeComponent* m_pBehaviourTree;

public:
	uint8 m_iTargetKeyID;

public:
	ARTSBaseAICharacterController();

	virtual void Possess(APawn* pawn) override;
	
};
