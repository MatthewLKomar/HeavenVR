// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GroundAnimalBase.h"
#include "GameFramework/Actor.h"
#include "Animal_Enums.h"
#include "BTTask_Harass.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENVR2_API UBTTask_Harass : public UBTTask_BlackboardBase
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
	//void DelayHolderFunction();
	//FVector PointMath(FVector StartLoc, int Distance, int Height);
//	void SetSpeed();
	
	bool LocationMath(AActor* ActorHarassing, int DistanceNeededToFollow, float BreathingRoom, FVector &ActorLocation); //Logic to Control Harassment
	FVector FollowActor(AActor * ActorHarassing, float BreathingRoom); //Stage 1 Harassment 
	FVector GetDirectionLoc(AActor * ActorHarassing, float BreathingRoom, int Direction=4);
	FVector GetInTheWay(AActor * ActorHarassing, float BreathingRoom); //Stage 2 Harassment 
	/*Gets the direction of the other actor between -1.0 (back), 1.0 (front)*/
	float DirectionFromActor(AActor* Actor);
	bool DebugLocation = false;
};
