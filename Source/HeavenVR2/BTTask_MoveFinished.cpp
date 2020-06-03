// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveFinished.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIC_Base.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

EBTNodeResult::Type UBTTask_MoveFinished::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto AIController = OwnerComp.GetAIOwner();
	Blackboard = OwnerComp.GetBlackboardComponent();
	if (AIController != nullptr)
	{
		AnimalBase = Cast<AGroundAnimalBase>(AIController->GetPawn());
	}
	if (AnimalBase != nullptr)
	{
		SetRandomWalkSpeedAndAcceleration();
		AnimalBase->PlayAnimation(EAnimType::Idle);
		UAnimMontage* AnimalMontage = AnimalBase->GetCurrentMontage();
		if (AnimalMontage)
		{
			GetWorld()->GetTimerManager().SetTimer(Delayer, this,
				&UBTTask_MoveFinished::DelayHolderFunction, AnimalMontage->GetPlayLength(), false);
		}
		GetWorld()->GetTimerManager().SetTimer(Delayer, this,
			&UBTTask_MoveFinished::DelayHolderFunction, WaitAtDestination, false);
		if (UseHomeBase)
		{
			//Set blackboard values(RoamBehavior)
			AnimalBase->RoamBehavior = EAIRoamBehavior::GoTOHomeBase;
		}
		else
		{
			SetBehaviorInTheBlackBoard(AnimalBase->SetRoamBehavior());
			AnimalBase->BiggestNeed = EGroundNaturalBehavior::Roam;
		}
		ResetWalkSpeedAndAcceleration();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}


void UBTTask_MoveFinished::DelayHolderFunction()
{
	//This doesn't really do anything 
}

void UBTTask_MoveFinished::SetRandomWalkSpeedAndAcceleration()
{
	UCharacterMovementComponent* CharacterMovement = AnimalBase->GetCharacterMovement();

	FVector2D LocationRange = AnimalBase->BehaviorLocation.WaitAtLocationRange;
	FVector2D AccelerationRange = AnimalBase->RandomMovement.AccelerationRange;
	AnimalBase->GetCharacterMovement()->MaxWalkSpeed =
		CharacterMovement->MaxWalkSpeed * UKismetMathLibrary::RandomFloatInRange(LocationRange.X, LocationRange.Y);
	AnimalBase->GetCharacterMovement()->MaxAcceleration =
		CharacterMovement->MaxAcceleration * UKismetMathLibrary::RandomFloatInRange(AccelerationRange.X, AccelerationRange.Y);
}

void UBTTask_MoveFinished::ResetWalkSpeedAndAcceleration()
{
	AnimalBase->GetCharacterMovement()->MaxWalkSpeed = AnimalBase->BehaviorDetails.MaxWalkSpeed;
	AnimalBase->GetCharacterMovement()->MaxAcceleration = AnimalBase->BehaviorDetails.MaxAcceleration;
}

void UBTTask_MoveFinished::SetBehaviorInTheBlackBoard(EAIRoamBehavior Selection)
{
	switch (Selection)
	{
	case EAIRoamBehavior::StayInPlace:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::StayInPlace);
		break;
	case EAIRoamBehavior::GoToRandomLocationInNavMesh:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoToRandomLocationInNavMesh);
		break;
	case EAIRoamBehavior::GoToRandomLocationWithinBounds:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoToRandomLocationWithinBounds);
		break;
	case EAIRoamBehavior::GoToRandomWayPoint:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoToRandomWayPoint);
		break;
	case EAIRoamBehavior::GoToRandomWayPointPath:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoToRandomWayPointPath);
		break;
	case EAIRoamBehavior::FollowWayPointPath:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::FollowWayPointPath);
		break;
	case EAIRoamBehavior::GoToNearestPOI:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoToNearestPOI);
		break;
	case EAIRoamBehavior::GoTOHomeBase:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoTOHomeBase);
		break;
	}
}
