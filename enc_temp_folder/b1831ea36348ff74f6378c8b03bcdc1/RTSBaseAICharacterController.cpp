// Niall Maple & Edward Hawksworth - 19/03/2018 ~

#include "RTSBaseAICharacterController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "UnrealGame/Character/RTSBaseCharacter.h"



ARTSBaseAICharacterController::ARTSBaseAICharacterController() :
	  m_iTargetKeyID(0)
	, m_iMoveCommandIssuedKeyID(0)
	, m_iMoveLocationKeyID(0)
	, m_bMoveCommandIssued(false)
	, m_vMoveLocation(FVector())
{
	m_pBlackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	m_pBehaviourTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTreeComponent"));
}

void ARTSBaseAICharacterController::Possess(APawn* pawn)
{
	Super::Possess(pawn);

	if (ARTSBaseCharacter* pChar = Cast<ARTSBaseCharacter>(pawn))
	{
		if (pChar->m_pBehaviourTree)
		{
			if (m_pBehaviourTree && m_pBlackboard)
			{
				m_pBlackboard->InitializeBlackboard(*pChar->m_pBehaviourTree->BlackboardAsset);
				m_iTargetKeyID = m_pBlackboard->GetKeyID("Target");
				m_iMoveLocationKeyID = m_pBlackboard->GetKeyID("MoveLocation");
				m_iMoveCommandIssuedKeyID = m_pBlackboard->GetKeyID("MoveCommandIssued");
				m_pBehaviourTree->StartTree(*pChar->m_pBehaviourTree);
			}
		}
	}
}