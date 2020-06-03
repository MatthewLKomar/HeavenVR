// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GroundAnimalBase.h"
#include "Animal_Enums.h"
#include "Animal_Structs.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTService_SetAIState.generated.h"

class AAIController;
/**
 * 
 */
UCLASS()
class HEAVENVR2_API UBTService_SetAIState : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_SetAIState();

	/** update next tick interval
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void SetBiggestNeed();
	void SetEngageBehavior();
	void SetNextBehaviorInBlackboard(EAIRoamBehavior Selection);
	void DelayHolderFunction();
	void CheckMovement();
	void CheckPlayerDistance();
	void SetNewCollision();
	void Disengage();
	void SetInactiveOptions();
	void PlayerFound();
	void SetAllComponentsOn(bool SetOn);
	void SetAIControllerOn(bool SetOn);
	void NoPlayerFound();
	void DetermineAIState();
	void DetermineAIState2();
	void DetermineAIState3();
	void SetBiggestNeedToFollowLeader();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName RunMode = TEXT("RunMode");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName State = TEXT("State");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName RoamBehavior = TEXT("RoamBehavior");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName BiggestNeed = TEXT("BiggestNeed");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName RunAway = TEXT("RunAway");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName Harass = TEXT("Harass");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName PredictiveMovement = TEXT("PredictiveMovement");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName EngageBehavior = TEXT("EngageBehavior");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName FoundBait = TEXT("FoundBait");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName FeedingBehavior = TEXT("FeedingBehavior");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName Resting = TEXT("Resting");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName DefenseState = TEXT("DefenseState");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName CustomTargetActive = TEXT("CustomTargetActive");

	UPROPERTY(BlueprintReadWrite, Category = CheckMovement)
		FVector CurrentLocation = FVector(0.0f,0.0f,0.0f);
	UPROPERTY(BlueprintReadWrite, Category = CheckMovement)
		FVector PreviousLocation = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(BlueprintReadWrite, Category = CheckMovement)
		int StuckCounter = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CheckMovement)
		FName Stuck = TEXT("Stuck");
	UPROPERTY(BlueprintReadWrite, Category = CheckMovement)
		float MinStuckDistance = 50.0f;
	UPROPERTY(BlueprintReadWrite, Category = CheckMovement)
		int MaxStuckTimes = 3;
	UPROPERTY(BlueprintReadWrite, Category = CheckMovement)
		float CollisionReductionPercent = 0.25f;
	UPROPERTY(BlueprintReadWrite, Category = CheckMovement)
		bool HasNewCollision = false;
	UPROPERTY(BlueprintReadWrite, Category = CheckMovement)
		float oCapsuleRadius = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = CheckMovement)
		float NewCollisionTime = 5.0f;
	UPROPERTY(BlueprintReadWrite, Category = CheckMovement)
		bool CheckMovementObstacles = false;
	UPROPERTY(BlueprintReadWrite, Category = CheckMovement)
		float ObstacleCheckFrequency = 1.0f;
	UPROPERTY(BlueprintReadWrite, Category = CheckMovement)
		bool DebugMovementObstacles =  false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CheckMovement)
		FName Moving = TEXT("Moving");
	UPROPERTY(BlueprintReadWrite, Category = CheckMovement)
		FVector SpawnLocation = FVector(0.0f,0.0f,0.0f);
	UPROPERTY(BlueprintReadWrite, Category = CheckMovement)
		int RelocateCounter = 0;
	UPROPERTY(BlueprintReadWrite, Category = CheckMovement)
		int RelocationChecks = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CheckMovement)
		FName EngageActor = TEXT("EngageActor");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CheckMovement)
		FTimerHandle ObstacleCheckHandler;
	
		
private:
	bool IsRunAway = true;
	bool DoOnce = true;
	bool DoOnce2 = true;
	float RadiusToActivate = 0.0f;
	AGroundAnimalBase* AnimalBase;
	AAIController* AIController;
	bool FoundPlayer = true;
	bool StopForEngageAnim = true;
	EAIState AIState;
	EMovementMode MovementMode;
	FAnimalBase_InactiveOptions InactiveOptions;
	FTimerHandle Delayer;
	UBlackboardComponent* Blackboard;

};
