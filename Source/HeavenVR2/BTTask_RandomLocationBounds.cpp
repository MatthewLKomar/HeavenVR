// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RandomLocationBounds.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIC_Base.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

EBTNodeResult::Type UBTTask_RandomLocationBounds::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto AIController = OwnerComp.GetAIOwner();
	Blackboard = OwnerComp.GetBlackboardComponent();

	if (AIController != nullptr)
	{
		AnimalBase = Cast<AGroundAnimalBase>(AIController->GetPawn());
	}
	if (AnimalBase != nullptr)
	{
		FVector ThisLocation = AnimalBase->GetActorLocation();
		auto InterestedActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (InterestedActor)
		{
			FVector TheirLocation = InterestedActor->GetActorLocation();//AnimalBase->EngagedActor->GetActorLocation();
			float DistanceBetween = FVector::Dist(ThisLocation, TheirLocation);
			if (DistanceBetween <= DistanceNeededToFollow && AnimalBase->Harass == false)
			{
				AnimalBase->Harass = true;
				return EBTNodeResult::Failed;
			}
		}
	//	else
		//{
			//UE_LOG(LogTemp, Warning, TEXT("No engaged actor"));
		//}
		
		UseHomeBase = AnimalBase->CanUseHomeBase;
		WaitAtDestination = UKismetMathLibrary::RandomFloatInRange(LocRange.X, LocRange.Y);
		SearchRadius = AnimalBase->BehaviorLocation.SearchRadius;
		MoveRadius = AnimalBase->MovementAcceptanceRadius;
		//Get new random location
		RandomLocation = UNavigationSystemV1::GetRandomPointInNavigableRadius(GetWorld(), AnimalBase->GetActorLocation(), SearchRadius);
		if (DebugLocation)
		{
			UE_LOG(LogTemp, Error, TEXT("AIState: %s"), *RandomLocation.ToString());
			UE_LOG(LogTemp, Error, TEXT("RandomLoc: %s"), *RandomLocation.ToString());
		}
		Blackboard->SetValueAsVector(TEXT("Vector"), RandomLocation);
		return EBTNodeResult::Succeeded;


	}
	return EBTNodeResult::Failed;

}

void UBTTask_RandomLocationBounds::DelayHolderFunction()
{
	//This doesn't really do anything 
}

