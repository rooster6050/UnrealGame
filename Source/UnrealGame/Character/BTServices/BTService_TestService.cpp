// Niall Maple & Edward Hawksworth - 19/03/2018 ~

#include "BTService_TestService.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "UnrealGame/Character/RTSBaseCharacter.h"
#include "UnrealGame/Character/RTSBaseAICharacterController.h"
#include "UnrealGame/Player/RTSPawn.h"
#include "UnrealGame/Player/RTSPlayerController.h"

UBTService_TestService::UBTService_TestService()
{
	bCreateNodeInstance = true;
}

void UBTService_TestService::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

/** Notify called after GameplayTask changes state from Active (finishing or pausing) */
void UBTService_TestService::OnGameplayTaskDeactivated(UGameplayTask& Task) {}

void UBTService_TestService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (ARTSBaseAICharacterController* pUnitPC = Cast<ARTSBaseAICharacterController>(OwnerComp.GetAIOwner()))
	{
		if (UBlackboardComponent* pBlackboard = OwnerComp.GetBlackboardComponent())
		{
			if (const UWorld* pWorld = GetWorld())
			{
				// Spectator Pawn - AKA the player/user
				if (ARTSPlayerController* PC = Cast<ARTSPlayerController>(pWorld->GetFirstPlayerController()))
				{
					// Initialising BB target value to the spectator pawn (player)
					pBlackboard->SetValue<UBlackboardKeyType_Object>(pUnitPC->m_iTargetKeyID, PC);
				}
				else
				{
					pBlackboard->SetValue<UBlackboardKeyType_Object>(pUnitPC->m_iTargetKeyID, NULL);
				}
			}
		}
	}
}