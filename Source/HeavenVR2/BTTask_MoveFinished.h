// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GroundAnimalBase.h"
#include "Animal_Enums.h"
#include "BTTask_MoveFinished.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENVR2_API UBTTask_MoveFinished : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	FName RoamBehavior = TEXT("RoamBehavior");
	FName Moving = TEXT("Moving");
	FBlackboardKeySelector Location;
private:
	AGroundAnimalBase* AnimalBase;
	float SearchRadius = 10000.0f;
	float WaitAtDestination = 5.0f;
	bool UseHomeBase = false;
	float MoveRadius = 100.0f;
	FVector RandomLocation = FVector(0.0f, 0.0f, 0.0f);
	bool DebugLocation = true;
	FVector2D LocRange;
	UBlackboardComponent* Blackboard;
	void DelayHolderFunction();
	void SetRandomWalkSpeedAndAcceleration();
	void ResetWalkSpeedAndAcceleration();
	void SetBehaviorInTheBlackBoard(EAIRoamBehavior Selection);

	bool InProgress = true;
	FTimerHandle Delayer;
};
