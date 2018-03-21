// Niall Maple & Edward Hawksworth - 19/03/2018 ~

#include "BTTask_TestTask.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "UnrealGame/Character/RTSBaseAICharacterController.h"
#include "UnrealGame/Player/RTSPlayerController.h"

EBTNodeResult::Type UBTTask_TestTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ARTSBaseAICharacterController* pUnitPC = Cast<ARTSBaseAICharacterController>(OwnerComp.GetAIOwner()))
	{
		if (UBlackboardComponent* pBlackboard = OwnerComp.GetBlackboardComponent())
		{
			// Some Condition
			if (pBlackboard->GetValue<UBlackboardKeyType_Bool>(pUnitPC->m_iMoveCommandIssuedKeyID))
			{
				// @ Params: Defaulted

				// NOTE: Maybe expose radius - and populate it based on target info - worry about this later though
				float fAcceptanceRadius = 1.0f;
				bool bStopOnOverlap = true;
				bool bUsePathfinding = true;
				bool bProjectDestinationToNavigation = false;
				bool bCanStrafe = true;
				TSubclassOf<UNavigationQueryFilter> filterClass = 0;
				bool bAllowPartialPath = true;
				EPathFollowingRequestResult::Type rv = pUnitPC->MoveToLocation(pUnitPC->m_vMoveLocation, fAcceptanceRadius, bStopOnOverlap, bUsePathfinding, bProjectDestinationToNavigation, bCanStrafe, filterClass, bAllowPartialPath);
				if (rv == EPathFollowingRequestResult::AlreadyAtGoal || rv == EPathFollowingRequestResult::Failed)
				{
					// Reached destination
					pUnitPC->m_bMoveCommandIssued = false; // Conclude this move instruction
					pBlackboard->SetValue<UBlackboardKeyType_Bool>(pUnitPC->m_iMoveCommandIssuedKeyID, pUnitPC->m_bMoveCommandIssued);
				}
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}