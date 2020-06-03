// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Materials/MaterialInterface.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AnimalBase.h"
#include "Animal_Enums.h"
#include "Animal_Structs.h"
#include "I_GroundAnimals.h"
#include "I_ATS_GroundAnimal.h"
#include "AI_POI_Base.h"
#include "GroundAnimalBase.generated.h"

/**
	*This  is the base class for all ground animals. 
	This is a child of the AnimalBase class and it inherits all parameters from it.
	This BP contains all main parameters for the ground animals. 
	You can configure all behavior parameters, such as Roam Mode, Roam Behavior, Engage Behavior, etc. 
	Here you will configure the details for all behaviors types.
	You can also set up the animal's animations and debug various behaviors.
 */

UCLASS()
class HEAVENVR2_API AGroundAnimalBase : public AAnimalBase//, public II_GroundAnimals, public II_ATS_GroundAnimal
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGroundAnimalBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USphereComponent* Collision_AI;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USphereComponent* Collision_Attack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,  Category = "Components" , meta = (AllowPrivateAccess = "true"))
		class UAIPerceptionComponent* AIPerception;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSource;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UAISenseConfig_Sight* sightConfig;


	//Setup behavior
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		FGroundAnimal_RandomAppearance RandomAppearance = { false, /*RandomSize*/FVector2D(0.9f,1.1f) /*Random Size In Range*/ };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		int MaxRandMaterial = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		EAIRoamBehavior RoamBehavior = EAIRoamBehavior::GoToRandomLocationInNavMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		ERoamMode RoamMode = ERoamMode::Specific;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		EEngageMethod EngageMethod = EEngageMethod::UseEngageTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		EGroundEngageBehavior EngageBehavior = EGroundEngageBehavior::Flee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		TArray<FName> EngageTags = { TEXT("abkPredator"), TEXT("abkPlayer") };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		TMap<FName, EGroundEngageBehavior> EngageMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		EEngageTargetBehavior EngageTargetBehavior = EEngageTargetBehavior::Fixated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		float MaxEngageDistance = 3000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		float MovementAcceptanceRadius = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		EGroundEngageBehavior GroundEngageBehavior = EGroundEngageBehavior::Flee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		bool CanUseHomeBase = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		AAI_POI_Base* HomeBase;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		FGroundAnimal_RandomMovement RandomMovement = { FVector2D(0.7f, 1.0f),FVector2D(0.5f, 1.0f),FVector2D(1.0f, 1.0f),FVector2D(1.0f, 1.0f) };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		FGroundAnimal_MovementObstruction MovementObstruction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		FGroundAnimalBehaviorAnimalDetails BehaviorDetails;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		FGroundAnimalBehaviorAnimalDetailsAttack BehaviorDetailsAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		FGroundAnimalBehaviorDefend BehaviorDefend;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		FGroundAnimalBehaviorLocation BehaviorLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		FGroundAnimalBehaviorFollowPath BehaviorFollowPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		FGroundAnimalBehaviorPOI BehaviorPOI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		EDefenseState DefenseState = EDefenseState::AttackEnemy;
	UPROPERTY(BlueprintReadWrite, Category = SetupBehavior)
		EGroundEngageBehavior OriginalEngageBehavior = EGroundEngageBehavior::Flee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		FGroundAnimal_Debug DebugAnimal;

	UPROPERTY(BlueprintReadWrite, Category = AIPereception)
		AActor* SensedActor;
	UPROPERTY(BlueprintReadWrite, Category = AIPereception)
		FAIStimulus RegisteredStimulus;
	UPROPERTY(BlueprintReadWrite, Category = AIPereception)
		bool Sight = false;
	UPROPERTY(BlueprintReadWrite, Category = AIPereception)
		bool Sound = false;
	UPROPERTY(BlueprintReadWrite, Category = AIPereception)
		bool Touch = false;
	UPROPERTY(BlueprintReadWrite, Category = AIPereception)
		bool Damage = false;
	UPROPERTY(BlueprintReadWrite, Category = AIPereception)
		FVector StimulusLocation;
	UPROPERTY(BlueprintReadWrite, Category = AIPereception)
		EStimulusDetected StimulusDetected = EStimulusDetected::Sight;
	UPROPERTY(BlueprintReadWrite, Category = AIPereception)
		bool EngageTagFound = false;
	UPROPERTY(BlueprintReadWrite, Category = AIPereception)
		AActor* EngagedActor;

	UPROPERTY(BlueprintReadWrite, Category = Companion)
		bool IsCompanion = false;
	UPROPERTY(BlueprintReadWrite, Category = Companion)
		FText CompanionName = FText::FromString("");
	UPROPERTY(BlueprintReadWrite, Category = Companion)
		bool NotifyNameChange = false;

	UPROPERTY(BlueprintReadWrite, Category = BBKeys)
		FName EngageActorKey = TEXT("EngageActor");
	UPROPERTY(BlueprintReadWrite, Category = BBKeys)
		FName FoundBaitKey = TEXT("FoundBait");
	UPROPERTY(BlueprintReadWrite, Category = BBKeys)
		FName DefenseStateKey = TEXT("DefenseState");

	UPROPERTY(BlueprintReadWrite, Category = SetupAnimations)
		int AnimIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupAnimations)
		FGroundAnimal_Animations IdleAnimations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupAnimations)
		FGroundAnimal_Animations AttackAnimations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupAnimations)
		FGroundAnimal_Animations DeathAnimations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupAnimations)
		FGroundAnimal_Animations HitAnimations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupAnimations)
		FGroundAnimal_Animations EatAnimations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupAnimations)
		FGroundAnimal_Animations DrinkAnimations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupAnimations)
		FGroundAnimal_Animations RestAnimations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupAnimations)
		bool StopForEngageAnim = true;
	UPROPERTY(BlueprintReadWrite, Category = SetupAnimations)
		int RandomAnimation = 0;
	UPROPERTY(BlueprintReadWrite, Category = SetupAnimations)
		FGroundAnimal_CurrentMontage CurrentAnimation;
	UPROPERTY(BlueprintReadWrite, Category = SetupAnimations)
		int SpecificAnimIndex = 0;
	UPROPERTY(BlueprintReadWrite, Category = SetupAnimations)
		float DeltaYaw = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupAnimations)
		bool CalculateAnimationYaw = false;
	UPROPERTY(BlueprintReadWrite, Category = SetupAnimations)
		FRotator CurrentRotation = FRotator(0.0f, 0.0f, 0.0f);
	UPROPERTY(BlueprintReadWrite, Category = SetupAnimations)
		FRotator PreviousRotation = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(BlueprintReadWrite, Category = SetupBreeding)
		bool WantsToBreed = false;
	UPROPERTY(BlueprintReadWrite, Category = SetupBreeding)
		AActor* NearbyPartner;

	UPROPERTY(BlueprintReadWrite, Category = Setup_AnimalDetails_Attack)
		float AggroCounter = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = Setup_AnimalDetails_Attack)
		FTimerHandle AggroTimerHandle;
	UPROPERTY(BlueprintReadWrite, Category = Setup_AnimalDetails_Attack)
		TArray<TEnumAsByte<EObjectTypeQuery>> DamageObjectTypes; //Apply damage to these object types
	UPROPERTY(BlueprintReadWrite, Category = Setup_AnimalDetails_Attack)
		bool Harass = false;
	UPROPERTY(BlueprintReadWrite, Category = AnimalControl)
		float BaseTurnRate = 45.0f;
	UPROPERTY(BlueprintReadWrite, Category = AnimalControl)
		float BaseLookUpRate = 45.0f;
	UPROPERTY(BlueprintReadWrite, Category = AnimalControl)
		float SprintSpeed = 2000.0f;
	UPROPERTY(BlueprintReadWrite, Category = AnimalControl)
		float WalkSpeed = 1000.0f;
	UPROPERTY(BlueprintReadWrite, Category = AnimalControl)
		float ZoomAmount = 25.0f;
	
	UPROPERTY(BlueprintReadWrite)
		EAIState AIState = EAIState::Inactive;
	UPROPERTY(BlueprintReadWrite)
		FTimerHandle NaturalNeedTimerHandle;
	UPROPERTY(BlueprintReadWrite)
		EGroundNaturalBehavior BiggestNeed = EGroundNaturalBehavior::Roam;
	UPROPERTY(BlueprintReadWrite)
		EAIRoamBehavior OriginalRoamBehavior = EAIRoamBehavior::StayInPlace;
	UPROPERTY(BlueprintReadWrite)
		AActor* OverlappedActor;
	UPROPERTY(BlueprintReadWrite)
		bool CanEngage = true;
	UPROPERTY(BlueprintReadWrite)
		AActor* McValidActor;
	UPROPERTY(BlueprintReadWrite)
		FTimerHandle PerceptionCheckHandler;
	UPROPERTY(BlueprintReadWrite)
		bool SetTextToEngaged = true;
	UPROPERTY(BlueprintReadWrite)
		bool SetTextToActive = false;
	UPROPERTY(BlueprintReadWrite)
		EMoveMode CurrentMovementMode = EMoveMode::Walk;
	UPROPERTY(BlueprintReadWrite)
		FTimerHandle SearchPlayerHandler;
	UPROPERTY(BlueprintReadWrite)
		FVector ActorScale = FVector(0, 0, 0);
	UPROPERTY(BlueprintReadWrite)
		UMaterialInterface* ActorMaterial;
	UPROPERTY(BlueprintReadWrite, Category = Setup)
		FTimerHandle AggroTimeHandle;



public: 
	
	//DECLARE_EVENT_FiveParams(AGroundAnimalBase, FTakeAnyDamageEvent, /*Type of Paramter 1*/,  /*Type of Paramter 2*/, /*Type of Paramter 3*/, /*Type of Paramter 4*/, /*Type of Paramter 5*/)
	//FTakeAnyDamageEvent& OnTakeAnyDamage() { return TakeAnyDamageEvent; }

	UFUNCTION(BlueprintCallable)
		void SaveOriginalBehaviors(); //Normally events
	UFUNCTION(BlueprintCallable)
		void BindToEventTakeDamage();//Normally events
	UFUNCTION(BlueprintCallable)
		void RandomAppearence();//Normally events
	UFUNCTION(BlueprintCallable)
		void SetCapsuleComponentLocationIfRagdolling();//Normally events
	UFUNCTION(BlueprintCallable)
		void YawCalculations();//Normally events
	UFUNCTION(BlueprintCallable)
		void CheckPerception();//Normally events
	UFUNCTION(BlueprintCallable)
		void IsValidActor(AActor* InActor, AActor*& OutActor, bool& Valid);
	UFUNCTION(BlueprintCallable)
		void CheckThatActorNotDead(AActor * CheckActor);
	UFUNCTION(BlueprintCallable)
		void SetDefenseLocation();
	UFUNCTION(BlueprintCallable)
		void SetEngageParams();
	UFUNCTION(BlueprintCallable)
		void CheckAggro(AActor * EngageActor);
	UFUNCTION(BlueprintCallable)
		void AggroTimer();
	UFUNCTION(BlueprintCallable)
		void CheckEngageActor2(AActor * EngageActor);
	UFUNCTION(BlueprintCallable)
		bool CheckForActorInMelee();
	UFUNCTION(BlueprintCallable)
		void Disengage();
	UFUNCTION(BlueprintCallable)
		void SetEngageTarget(AActor* ActorSensed);
	UFUNCTION(BlueprintCallable)
		void PerceptionUpdated(const TArray<AActor*>& UpdatedActors);
	UFUNCTION(BlueprintCallable)
		void TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION(BlueprintCallable)
		void ModifyEngageBehavior(AActor * Actor, AActor *& EngageActor, bool & CanBeEngaged);
	UFUNCTION(BlueprintCallable)
		void EngagementStart();
	UFUNCTION(BlueprintCallable)
		void EngagementEnd();
	UFUNCTION(BlueprintCallable)
		void GroupEngageBehavior();
	UFUNCTION(BlueprintCallable)
		bool CheckDestination(FVector RandomLoc);
	UFUNCTION(BlueprintCallable)
		void PlayAnimation(EAnimType AnimationType);
	UFUNCTION(BlueprintCallable)
		EAIRoamBehavior SetRoamBehavior();
	UFUNCTION(BlueprintCallable)
		void SearchForPlayer();
	UFUNCTION(BlueprintCallable)
		EGroundEngageBehavior DetermineEngageBehavior(EGroundEngageBehavior TagEngageBehavior);
	UFUNCTION(BlueprintCallable)
		void EngageStuff(AActor* Actor);

private:

	FVector DefenseLocation = FVector(0.0f, 0.0f, 0.0f);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
