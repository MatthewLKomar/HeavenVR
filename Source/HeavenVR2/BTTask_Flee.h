// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GroundAnimalBase.h"
#include "GameFramework/Actor.h"
#include "Animal_Enums.h"
#include "BTTask_Flee.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENVR2_API UBTTask_Flee : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	/** starts this task, should return Succeeded, Failed or InProgress
		* (use FinishLatentTask() when returning InProgress)
		* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	FName RoamBehavior = TEXT("RoamBehavior");
	FName Moving = TEXT("Moving");
	FBlackboardKeySelector Location;
private:
	AGroundAnimalBase* AnimalBase;
	UBlackboardComponent* Blackboard;
	void DelayHolderFunction();
	float DirectionFromActor(AActor* Actor);
	FVector PointMath(FVector StartLoc, int Distance, int Height);
	void SetRunAtMaxSpeed();
	FVector LocationMath(AActor* ActorFleeingFrom, int DistanceMin, int DistanceMax, int Height);
	bool DebugLocation = true;
};
