// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RandomWayPoint.h"
#include "GameFramework/Character.h"
#include "AI_WayPoint.h"
#include "NavigationSystem.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIC_Base.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"


EBTNodeResult::Type UBTTask_RandomWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto AIController = OwnerComp.GetAIOwner();
	//OwnerComp = PawnRef
	//auto AnimalController = Cast<AAIC_Base>(OwnerComp.GetAIOwner());
	Blackboard = OwnerComp.GetBlackboardComponent();

	if (AIController != nullptr)
	{
		AnimalBase = Cast<AGroundAnimalBase>(AIController->GetPawn());
	}
	if (AnimalBase != nullptr)
	{
		TArray<AActor*> TargetPointsFound;
		UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), AAI_WayPoint::StaticClass(), TargetPointsFound);
		if (TargetPointsFound.Num() >= 1) //need to do a null check to make sure we have an array, else we might crash
		{
			Blackboard->SetValueAsVector(TEXT("Vector"), TargetPointsFound[0]->GetActorLocation());
			return EBTNodeResult::Succeeded;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No waypoints found"));
		}
	}
	return EBTNodeResult::Failed;
}

void UBTTask_RandomWayPoint::DelayHolderFunction()
{
	//This doesn't really do anything 
}
void UBTTask_RandomWayPoint::SetRandomWalkSpeedAndAcceleration()
{
	UCharacterMovementComponent* CharacterMovement = AnimalBase->GetCharacterMovement();

	FVector2D LocationRange = AnimalBase->BehaviorLocation.WaitAtLocationRange;
	FVector2D AccelerationRange = AnimalBase->RandomMovement.AccelerationRange;
	AnimalBase->GetCharacterMovement()->MaxWalkSpeed =
		CharacterMovement->MaxWalkSpeed * UKismetMathLibrary::RandomFloatInRange(LocationRange.X, LocationRange.Y);
	AnimalBase->GetCharacterMovement()->MaxAcceleration =
		CharacterMovement->MaxAcceleration * UKismetMathLibrary::RandomFloatInRange(AccelerationRange.X, AccelerationRange.Y);
}

void UBTTask_RandomWayPoint::ResetWalkSpeedAndAcceleration()
{
	AnimalBase->GetCharacterMovement()->MaxWalkSpeed = AnimalBase->BehaviorDetails.MaxWalkSpeed;
	AnimalBase->GetCharacterMovement()->MaxAcceleration = AnimalBase->BehaviorDetails.MaxAcceleration;
}

void UBTTask_RandomWayPoint::SetBehaviorInTheBlackBoard(EAIRoamBehavior Selection)
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