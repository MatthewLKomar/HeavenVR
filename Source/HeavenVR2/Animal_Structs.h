// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Animal_Enums.h"
#include "GameFramework/Actor.h"
#include "AI_BoundingBox.h"
#include "AI_Path.h"
#include "Materials/MaterialInterface.h"
#include "Animation/AnimMontage.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundAttenuation.h"
#include "Sound/SoundConcurrency.h"
#include "Animal_Structs.generated.h"


class AAI_DefentLocation;
class AGroundAnimalBase;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FGroupManagerSettings 
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGroupManager_EngageBehavior EngageBehaviorMethod = EGroupManager_EngageBehavior::UseGroupEngageBehavior;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGroundEngageBehavior GroupEngageBehavior = EGroundEngageBehavior::Ignore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool ChooseRandomLeader = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NewLeaderRate = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool NoDamageByMembers = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName GroupTag = TEXT("Group1");
};

USTRUCT(BlueprintType)
struct FAutoGroup_SpeciesDetail
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Species = FText::FromString("Animal");
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D GroupSize = FVector2D(3.0f, 3.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAutoGroup_AnimalType Leader = EAutoGroup_AnimalType::Male;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAutoGroup_AnimalType GroupComposition = EAutoGroup_AnimalType::Female;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGroupManagerSettings GroupManagerSettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector GroupManagerSpawnLocation = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AGroundAnimalBase*> MaleList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AGroundAnimalBase*> FemaleList;
};

USTRUCT(BlueprintType)
struct FAnimalBase_AnimalDeath
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DespawnTimer = 10.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bRagdollBody = false;

};
USTRUCT(BlueprintType)
struct FAnimal_Detail
{
	GENERATED_BODY()
		//In the blueprint there's HUD info stuff
		//We won't have HUD stuff though
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText AnimalName = FText::FromString("Animal");
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAnimalSex Sex = EAnimalSex::Male;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Species = FText::FromString("Prey");
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AnimalHP = 10.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> NoDamageTags;

};

USTRUCT(BlueprintType)
struct FAnimalBase_InactiveOptions {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bMakeVisibleWhenInactive = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDisableCollisionWhileInactive = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool StopActorTick = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DisableAllComponents_aggresive = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DisableAIController = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool StopAILogic = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DespawnWhenInactive = false;
};

USTRUCT(BlueprintType)
struct FAnimalBase_SimDetails {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAIRunMode AIRunMode = EAIRunMode::RunOnProximity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RadiusToActivate = 30000.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PlayerCheckFrequency = 5.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAnimalBase_InactiveOptions InactiveOptions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bUsePredictiveMovement = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PredictiveMovementUpdateRate = 20.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName NoSpawnTag = TEXT("abkNoSpawn");
};
USTRUCT(BlueprintType)
struct FAnimalBase_AnimalDetails{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText AnimalName = FText::FromString("Animal");
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAnimalSex Sex = EAnimalSex::Male;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Species = FText::FromString("Prey");
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AnimalHealth = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> NoDamageTags;

};

USTRUCT(BlueprintType)
struct FGroundAnimalBehaviorLocation {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D WaitAtLocationRange = FVector2D(2.0, 6.0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AAI_BoundingBox* BoundsReference;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SearchRadius = 5000.0;
};

USTRUCT(BlueprintType)
struct FGroundAnimalBehaviorFollowPath {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EPathSelection PathSelection = EPathSelection::Specific;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AAI_Path* PathToFollow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int StartingWayPoint = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D WaitAtWayPointRange = FVector2D(2.0, 4.0);
};

USTRUCT(BlueprintType)
struct FGroundAnimalBehaviorPOI {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float POIWaitTime = 60.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D POIWaitTimeRange = FVector2D(45.0, 60.0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int NumberOfMovesInPOI = 2;
};

USTRUCT(BlueprintType)
struct FAnimalSpawner_AnimalList {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> AnimalClass; //class refernce 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int NumberToSpawn = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAIRoamBehavior RoamBehavior = EAIRoamBehavior::GoToRandomLocationInNavMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGroundEngageBehavior EngageBehavior = EGroundEngageBehavior::Ignore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGroundAnimalBehaviorLocation BehaviorLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGroundAnimalBehaviorFollowPath BehaviorFollowPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGroundAnimalBehaviorPOI BehaviorPointOfInterest;
};

USTRUCT(BlueprintType)
struct FGroundAnimal_Debug {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool RoamBehavior = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool EngagedTarget = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool MeleeeRange = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool PlayerProximityCheck = false;
};

USTRUCT(BlueprintType)
struct FGroundAnimalBehaviors_AnimalBehaviors {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EFeedingBehavior FeedingBehavior =  EFeedingBehavior::Prey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxWalkSpeed = 1200.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EngageMaxWalkSpeed = 1200.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxAcceleration = 1000.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EngageMaxAcceleration = 1000.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HurtMovementFactor = 0.5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Mass = 100.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxStepHeight = 45.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxWalkableFloorAngle = 50.0;
};

USTRUCT(BlueprintType)
struct FPopulation_GroundAnimalBehaviors {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Population_GroundAnimalBehaviors Struct")
		bool bOverrideBehaviors = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Population_GroundAnimalBehaviors Struct")
		EAIRoamBehavior RoamBehvaior = EAIRoamBehavior::StayInPlace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Population_GroundAnimalBehaviors Struct")
		EGroundEngageBehavior EnageBehavior = EGroundEngageBehavior::Flee;
};

USTRUCT(BlueprintType)
struct FGroundAnimal_RandomMovement {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GroundAnimal_RandomMovement Struct")
		FVector2D WalkSpeedRange = FVector2D(1.0,1.0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GroundAnimal_RandomMovement Struct")
		FVector2D AccelerationRange = FVector2D(1.0, 1.0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GroundAnimal_RandomMovement Struct")
		FVector2D EngageWalkSpeedRange = FVector2D(1.0, 1.0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GroundAnimal_RandomMovement Struct")
		FVector2D EngageAccelerationRange = FVector2D(1.0, 1.0);
}; 

USTRUCT(BlueprintType)
struct FGroundAnimal_RandomAppearance{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GroundAnimal_RandomAppearance Struct")
		bool bRandomizeSize = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GroundAnimal_RandomAppearance Struct")
		FVector2D randomSizeInRange = FVector2D(0.1, 1.2);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GroundAnimal_RandomAppearance Struct")
		bool bRandomizeMaterial = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GroundAnimal_RandomAppearance Struct")
		TArray<UMaterialInterface*> MaterialList; 
};


USTRUCT(BlueprintType)
struct FGroundAnimal_MovementObstruction {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bActive = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CheckFrequency = 1.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MinimumStuckDistance = 25.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxObstructedChecks = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxChecksForRelocation = 6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CollisionReductionPercent = 25.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ModifiedCollisionTime = 5.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bDebug = false;
};

USTRUCT(BlueprintType)
struct FGroundAnimalBehaviorAnimalDetails {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EFeedingBehavior FeedingBehavior = EFeedingBehavior::Prey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxWalkSpeed = 1200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EngageMaxWalkSpeed = 1200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxAcceleration = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EngageMaxAcceleration = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HurtMovementFactor = .5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Mass = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxStepHeight = 45.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxWalkableFloorAngle = 50.0f;
};

USTRUCT(BlueprintType)
struct FGroundAnimalBehaviorAnimalDetailsAttack {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EMeleeDamage MeleeDamageType = EMeleeDamage::SingleDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageAmount = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackFrequency = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AggroTimer = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DisengageCD = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool DontMoveWhileAttacking = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool AccurateTargetDetection = true;
};

USTRUCT(BlueprintType)
struct FGroundAnimalBehaviorDefend {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxDistanceFromLocation = 5000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EDefenseLocation DefenseLocationType = EDefenseLocation::CurrentLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AAI_DefentLocation* SpecificDefenseLocation;
};

USTRUCT(BlueprintType)
struct FPopulation_AnimalDetails{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* AnimalReference;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Species;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAnimalSex Sex = EAnimalSex::Male;

};

USTRUCT(BlueprintType)
struct FGroundAnimal_CurrentMontage {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool AnimationPlaying = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAnimType AnimationType = EAnimType::Idle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MontageIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AnimationPlayrate = 0.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* MontageReference;
};

USTRUCT(BlueprintType)
struct FGroundAnimal_AnimationDetails {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* AnimationMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AnimationPlayRate = 1.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName AnimationStartSectionName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* SoundCue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SoundVolumeMultiplier = 1.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SoundPitchMultiplier = 1.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SoundStartTime = 1.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundAttenuation* SoundAttenuation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundConcurrency* SoundConcurrencySettings;
};

USTRUCT(BlueprintType)
struct FGroundAnimal_Animations {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FGroundAnimal_AnimationDetails> AnimationsList; //TODO:init with one array element
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAnimPlayMode PlayMode = EAnimPlayMode::Single;
};

UCLASS()
class HEAVENVR2_API UAnimal_Structs : public UUserDefinedStruct
{
	GENERATED_BODY()
	
};
