// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GroundAnimalBase.h"
#include "Animal_Enums.h"
#include "BTTask_RandomWayPoint.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENVR2_API UBTTask_RandomWayPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	/** starts this task, should return Succeeded, Failed or InProgress
	 * (use FinishLatentTask() when returning InProgress)
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	FName WayPoint = TEXT("WayPoint");
	FName Moving = TEXT("Moving");
private:
	AGroundAnimalBase* AnimalBase;
	TArray<AActor*> WayPointsFound;
	float WaitAtDestination = 5.0f;
	FName RoamBehavior = TEXT("RoamBehavior");
	bool UseHomeBase = false;
	float MoveRadius = 100.0f;
	float SearchRadius = 10000.0f;
	bool DebugLocation = true;
	FVector2D LocRange;
	FVector Destination = FVector(0.0f, 0.0f, 0.0f);
	UBlackboardComponent* Blackboard;

	void DelayHolderFunction();
	void SetRandomWalkSpeedAndAcceleration();
	void ResetWalkSpeedAndAcceleration();
	void SetBehaviorInTheBlackBoard(EAIRoamBehavior Selection);

	bool InProgress = true;
	FTimerHandle Delayer;
};
