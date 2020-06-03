// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "Animal_Enums.generated.h"

/**
 * 
 */
UENUM()
enum class EAutoGroup_AnimalType : uint8
{
	Male,
	Female,
	Random
};

UENUM()
enum class EAnimalSpawner_SpawnMethod : uint8
{
	BeginPlay, //Spawn animal as soon as the game starts
	OverlapTrigger, //Spawn animal when Player overlaps trigger
	Inactive //Spawner will remain inactive until a BP_AnimalSpawner_Trigger activates it
};

UENUM()
enum class EAnimalType : uint8
{
	GroundAnimal,
	FlyingAnimal,
	SwimmingAnimal 
};

UENUM()
enum class EAnimalSex : uint8
{
	Male,
	Female
};

UENUM()
enum class EAnimalSpawner : uint8
{
	KillAnimals, //Kills the animal by using the Death event
	DestroyAnimals //Destroys the animal by using Destroy Actor
};

UENUM()
enum class EAIRunMode : uint8
{
	RunOnProximity, //Run AI simulation ONLY within a certain distance of the Player pawn
	AlwaysRun, //Run AI simulation regardless of distance to Player pawn
	UseActivationManager //Use the Activation Manager to determine if the AI is Active or Inactive
};

UENUM()
enum class EAIDirector_ActiveMode : uint8{
	Active,
	UseTag
};

UENUM()
enum class EAIDirector_AllModes : uint8 {
	MoveToTargetLocation,
	ActivateBehavior
};

UENUM()
enum class EAIRoamBehavior : uint8 {
//This enum defines the Roaming Behavior of the Ground AI
	StayInPlace, //AI will stay in its original location unless it Engages
	GoToRandomLocationInNavMesh, //AI will go to a random location within the Navmesh
	GoToRandomLocationWithinBounds, //AI will go to a random location within the Bounds
	GoToRandomWayPoint,//AI will go to a random WayPoint
	GoToRandomWayPointPath,
	FollowWayPointPath, //AI will follow a predetermined path (patrol)
	GoToNearestPOI, //AI will find the nearest POI and go to it
	GoTOHomeBase //AI will go to specified Home Base POI
};

UENUM()
enum class EAIState : uint8 {
	Inactive, //AI is inactive because Player is too far
	Active, //AI is roaming the environment based on its specific Need
	Engaged, //Ai is Engaged based on its Engage Behavior
	FoundBait, //AI found neraby bait
	PartOfGroup, //AI is part of a group
	Dead //AI is dead
};

UENUM()
enum class EAnimPlayMode : uint8 {
	Single, //Play the first animation in the array
	Random, //Play a random animation from the array
	Sequential,//Play all animations in the array in a sequential manner
	Specific//Add your own logic to decide which animation plays
};

UENUM()
enum class EAnimType : uint8 {
//This enum contains all animal animations used as animation montages
	//plays its respective animations
	Idle,
	Engage,
	Attack,
	Death,
	Hit,
	Eat,
	Drink,
	Rest
};

UENUM()
enum class ECompanion_TameMode : uint8 {
	UseBait, //Player has to use the right type of Bait to tame the Companion
	AlwaysTamable //Player can tame the companion at any time by getting near it
};

UENUM()
enum class ECompanion_Stance : uint8 {
//Stance for Player Companion	
	Passive, //Companion will not attack unless commanded
	Aggresive //Companion will attack any enemy that attacks it or its Owner
};

UENUM()
enum class ECompanion_Tasks : uint8 {
	//This enum describes all the possible abilities a Companion can have
	FollowOwner,
	StayInPlace,
	GoToLocationAndWait,
	Attack,
	Leave
};

UENUM()
enum class ECustomNeedModes : uint8 {
//This enum specifies the different modes for Comp_CustomNeed
	SingleActor, //Go to single actor specified
	ClosestActorFromClass,//Go to nearest actor of the specified class
	CustomEvent //Execute custom event
};
UENUM()
enum class ESwimMode : uint8 {
	FlockHeavy,
	SoloLight
};

UENUM()
enum class EFlyMode : uint8 {
	FlockHeavy,
	SoloLight
};

UENUM()
enum class EDefenseLocation : uint8 {
	CurrentLocation,
	SpecificLocation
};

UENUM()
enum class EDefenseState : uint8 {
	GoingToDefenseLocation,
	AttackEnemy
};
UENUM()
enum class EEngageMethod : uint8 {
	UseEngageTags,
	UseEngageMap_Experimental

};

UENUM()
enum class EEngageTargetBehavior : uint8 {
	Fixated,  //AI will engage first target and stick to it
	Nearest //AI will engage the closest target
};

UENUM()
enum class EFeedingBehavior : uint8 {
	Prey,
	Predator
};

UENUM()
enum class EBaitTypeATS : uint8 {
	Prey,
	Predator
};

UENUM()
enum class EBaitType : uint8 {
	Prey,
	Predator
};

UENUM()
enum class EGroundEngageBehavior : uint8 {
//This enum describes the possible Engage Behaviors
	Ignore, //AI will ignore EngageActor and continue Active Behavior
	Flee, //AI will run away from EngageActor
	TryToHide, //AI will try to hide from EngageActor
	Defend,//AI will attack EngageActor if in range, but will NOT pursue
	Attack//AI will attack EngageActor and will pursue
};

UENUM()
enum class EGroundNaturalBehavior : uint8 {
//This enum describes the natural needs for the Ground Animals
	Eat,
	Drink,
	Breed,
	Roam,//AI can roam around freely
	Rest, //AI needs to rest (usually connected to night time)
	CustomNeed, //AI will execute a Custom Need from Comp_CustomNeed
	FollowParent, //AI will simply follow its parent
	FollowLeader //AI will follow the group leader

};

UENUM()
enum class EGroupManager_EngageBehavior : uint8 {
	UseGroupEngageBehavior,
	UseLeaderEngageBehavior,
	USeIndividualEngageBehaviors
};

UENUM()
enum class EGroupMode : uint8 {
	Manual, //Specify the Group Manager manually
	AutoGroup, //Let BP_AutoGroupManager handle the group
	AutoGroupWithTag //Register with a speciifc AutoGroupManager with a specific tag

};

UENUM()
enum class EMeleeDamage : uint8 {
	SingleDamage, //hits one actor
	AreaOfEffectDamage //hits everyone nearby
};



UENUM()
enum class EPathSelection : uint8 {
	Specific, //AI will only go on the specified path
	Nearest //Ai will follow the closest path found
};

UENUM()
enum class EReferenceMode : uint8 {
	Manual, //Manually set the references
	Automatic //Automatically set the references. 
	//^^This will use the first actor it finds as a reference, so use with caution
};


UENUM()
enum class EReferenceModePopulation : uint8 {
	Automatic, //Automatically get the Population Control reference
	UseTag //Use a unique tag to get the Population Control reference
};

UENUM()
enum class ERoamMode : uint8 {
	Specific,  //Only use specified Roam Behavior
	Random //Pick a random Roam Behavior once current behavior is finished
};

UENUM()
enum class EStimulusDetected : uint8 {
	Sight,
	Sound,
	Touch,
	Damage,
	SeveralSenses
};

UENUM()
enum class EMoveMode : uint8 {
	//originally called EMovementMode
	Walk,
	Swim,
	Climb,
	Fly

};

UCLASS()
class HEAVENVR2_API UAnimal_Enums : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};
