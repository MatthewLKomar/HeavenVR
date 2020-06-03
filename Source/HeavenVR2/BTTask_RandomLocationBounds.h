// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GroundAnimalBase.h"
#include "Animal_Enums.h"
#include "BTTask_RandomLocationBounds.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENVR2_API UBTTask_RandomLocationBounds : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	/** starts this task, should return Succeeded, Failed or InProgress
	 * (use FinishLatentTask() when returning InProgress)
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	FName RoamBehavior = TEXT("RoamBehavior");
	FName Moving = TEXT("Moving");
	FBlackboardKeySelector Location;
private:
	AGroundAnimalBase* AnimalBase;
	float SearchRadius = 10000.0f;
	int DistanceNeededToFollow = 2000;
	float WaitAtDestination = 5.0f;
	bool UseHomeBase = false;
	float MoveRadius = 100.0f;
	FVector RandomLocation = FVector(0.0f, 0.0f, 0.0f);
	bool DebugLocation = false;
	FVector2D LocRange;
	UBlackboardComponent* Blackboard;
	void DelayHolderFunction();
	
	bool InProgress = true;
	FTimerHandle Delayer;
};
