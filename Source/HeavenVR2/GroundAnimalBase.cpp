#include "GroundAnimalBase.h"
#include "GroundAnimalBase.h"
#include "GroundAnimalBase.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundAnimalBase.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI_DefentLocation.h"
#include "CompGroup.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"


AGroundAnimalBase::AGroundAnimalBase()
{
	// Setup the perception component
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	AIPerception->ConfigureSense(*sightConfig);
	AIPerception->SetDominantSense(sightConfig->GetSenseImplementation());
	AIPerception->OnPerceptionUpdated.AddDynamic(this, &AGroundAnimalBase::PerceptionUpdated);
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AGroundAnimalBase::TargetPerceptionUpdated);

	//Setup for Collisions
	Collision_AI = CreateDefaultSubobject<USphereComponent>(TEXT("Collision_AI"));
	Collision_AI->SetupAttachment(GetRootComponent());
	Collision_AI->SetSphereRadius(250.0f);

	Collision_Attack = CreateDefaultSubobject<USphereComponent>(TEXT("Collision_Attack"));
	Collision_Attack->SetupAttachment(GetRootComponent());

	GetCharacterMovement()->Mass = BehaviorDetails.Mass;
	GetCharacterMovement()->MaxAcceleration = BehaviorDetails.MaxAcceleration;
	GetCharacterMovement()->MaxStepHeight = BehaviorDetails.MaxStepHeight;
	GetCharacterMovement()->SetWalkableFloorAngle(BehaviorDetails.MaxWalkableFloorAngle);
	switch (BehaviorDetails.FeedingBehavior)
	{
	case EFeedingBehavior::Prey:
		ActorTags.Add(TEXT("abkPrey"));
		break;
	case EFeedingBehavior::Predator:
		ActorTags.Add(TEXT("abkPredator"));
		break;
	}
	ActorTags.Add((FName(*AnimalDetails.Species.ToString()))); //Conversion of FText to Fname. There is no direct conversion.
	ActorTags = Tags;
	EngageMap.Add(TEXT("abkPredator"), EGroundEngageBehavior::Flee);
	EngageMap.Add(TEXT("abkPlayer"), EGroundEngageBehavior::Flee);

}

// Called when the game starts or when spawned
void AGroundAnimalBase::BeginPlay()
{
	Super::BeginPlay();
	SaveOriginalBehaviors();
	BindToEventTakeDamage();
	RandomAppearence();

	

}

// Called every frame
void AGroundAnimalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetCapsuleComponentLocationIfRagdolling();
	YawCalculations();
}

void AGroundAnimalBase::SaveOriginalBehaviors()
{
	OriginalRoamBehavior = RoamBehavior;
	OriginalEngageBehavior = EngageBehavior;
}

void AGroundAnimalBase::BindToEventTakeDamage()
{
	
	// Call this when u wanna broadcast
	//TakeAnyDamageEvent.Broadcast();

	//Call this when u wanna bind a function to an event
	//TakeAnyDamageEvent.BindUObject( /*Put ur class name here*/, &/*Put ur class name here*/::/*Put ur function name here*/);

}

void AGroundAnimalBase::RandomAppearence()
{
	if (RandomAppearance.bRandomizeSize == true)
	{
		FVector MeshScale = GetMesh()->RelativeScale3D;
		float RandomScale = FMath::FRandRange(RandomAppearance.randomSizeInRange.X, RandomAppearance.randomSizeInRange.Y);
		ActorScale = MeshScale *= RandomScale;
	}
	if (RandomAppearance.bRandomizeMaterial == true && RandomAppearance.MaterialList.IsValidIndex(0))
	{
		//Random from 0 to last index
		//going to limit random material length to 4 for now
		//if you want more change that integer variable
		int RandomIndex = FMath::FRandRange(0, MaxRandMaterial-1);
		ActorMaterial = RandomAppearance.MaterialList[RandomIndex];
	}

}

void AGroundAnimalBase::SetCapsuleComponentLocationIfRagdolling()
{
	if (Death_Details.bRagdollBody && Dead)
	{
		FVector NewLocation = GetMesh()->GetComponentLocation();//In blueprint terms this is GetWorldLocation()
		GetCapsuleComponent()->SetWorldLocation(NewLocation, false, 0, ETeleportType::ResetPhysics);

	}
}

void AGroundAnimalBase::YawCalculations()
{
	if (CalculateAnimationYaw == true)
	{
		PreviousRotation = CurrentRotation;
		CurrentRotation = GetActorRotation();
		float Yaw = UKismetMathLibrary::NormalizedDeltaRotator(CurrentRotation, PreviousRotation).Yaw;
		DeltaYaw = UKismetMathLibrary::FInterpTo(DeltaYaw, Yaw, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 1.0f);
	}
}

void AGroundAnimalBase::CheckPerception()
{
	AIPerception->RequestStimuliListenerUpdate();
}

void AGroundAnimalBase::IsValidActor(AActor * InActor, AActor *& OutActor, bool& Valid)
{
	//Are we part of a group ?
	UCompGroup* Component = FindComponentByClass<UCompGroup>();
	//Are we active in the group and is the Group Manager reference valid?
	if (Component != nullptr)
	{
		if (Component->GroupManager != nullptr)
		{
			InActor->ActorHasTag(Component->GroupManager->GroupTag);
		}
	}
	CheckThatActorNotDead(InActor);
	switch (EngageMethod)
	{
	case EEngageMethod::UseEngageTags:
		for (FName Tag : EngageTags)
		{
			if (InActor->Tags.Contains(Tag))
			{
				EngageTagFound = true;
				break;
			}
			
		}
		break;
	case EEngageMethod::UseEngageMap_Experimental:
		//Not going to be used
		TArray<FName> Keys;
		EngageMap.GetKeys(Keys);
		for (FName Tag : Keys)
		{
			if (InActor->Tags.Contains(Tag))
			{
			}
		}
		break;
	}
	//Check if any engagement tags where found. If so, also make sure that the engage actor is within the MaxEngageDistance
	float DistanceFromActors = (InActor->GetActorLocation() - GetActorLocation()).Size();
	if ((DistanceFromActors <= MaxEngageDistance) && EngageTagFound)
	{
		Valid = true;
	}
	else
	{
		Valid = false;
	}

}

void AGroundAnimalBase::CheckThatActorNotDead(AActor* CheckActor)
{
	if (!CheckActor->ActorHasTag(TEXT("abkDead")))
	{
		EngageTagFound = false;
	}
}
void AGroundAnimalBase::SetDefenseLocation()
{
	//If this is false, we don't need to set a defense location
	if (EngageBehavior == EGroundEngageBehavior::Defend)
	{
		switch (BehaviorDefend.DefenseLocationType)
		{
			case EDefenseLocation::CurrentLocation:
				DefenseLocation = GetActorLocation();
				break;
			case EDefenseLocation::SpecificLocation:
				DefenseLocation = BehaviorDefend.SpecificDefenseLocation->GetActorLocation();
				break;
		}
	}
}

void AGroundAnimalBase::SetEngageParams()
{
	if (UAIBlueprintHelperLibrary::GetAIController(this) != nullptr)
	{
		//Change Max WalkSpeed
		GetCharacterMovement()->MaxWalkSpeed = BehaviorDetails.EngageMaxWalkSpeed;
		//Change Max Acceleration
		GetCharacterMovement()->MaxAcceleration = BehaviorDetails.EngageMaxAcceleration;
		//Get first perceived actor and set it as EngageActor in the Blackboard
		UBlackboardComponent* Blackboard = UAIBlueprintHelperLibrary::GetAIController(this)->GetBlackboardComponent();
		Blackboard->SetValueAsObject(EngageActorKey, EngagedActor);
		SetDefenseLocation();
		Engaged = true;
	}
	if (SetTextToEngaged)
	{
		SetTextToEngaged = false;
	}
	else
	{
		SetTextToEngaged = true;
	}

}

void AGroundAnimalBase::CheckAggro(AActor* EngageActor)
{
	if (EngageActor == EngagedActor)
	{
		UKismetSystemLibrary::K2_UnPauseTimerHandle(GetWorld(), AggroTimerHandle);
		AggroTimer();

	}
}

void AGroundAnimalBase::AggroTimer()
{
	GetWorld()->GetTimerManager().SetTimer(AggroTimeHandle, this, &AGroundAnimalBase::AggroTimer, 1.0f, true);
	//->GetTimerManager().SetTimer(AggroTimeHandle, this, &AGroundAnimalBase::AggroTimer, 1.0f, true);
	if (AggroCounter >= BehaviorDetailsAttack.AggroTimer)
	{
		UKismetSystemLibrary::K2_PauseTimerHandle(GetWorld(), AggroTimerHandle);
		AggroCounter = 0.0f;
		Disengage();
	}
	else
	{
		AggroCounter++;
	}

}


void AGroundAnimalBase::CheckEngageActor2(AActor* EngageActor)
{
	if (!Engaged)
	{
		CheckAggro(EngageActor);
		AggroCounter = 0.0f;
	}
}
bool AGroundAnimalBase::CheckForActorInMelee()
{
	return false;
}
void AGroundAnimalBase::Disengage()
{
	if (CheckForActorInMelee())
	{
		CheckPerception();
	}
	else
	{
		EngagedActor = nullptr;
		Engaged = false;
		GetCharacterMovement()->MaxWalkSpeed = BehaviorDetails.MaxWalkSpeed;
		GetCharacterMovement()->MaxAcceleration = BehaviorDetails.MaxAcceleration;
		EngagementEnd();
		if (SetTextToActive)
		{
			SetTextToActive = false;
		}
		else
		{
			SetTextToActive = true;
		}
	}
}

void AGroundAnimalBase::SetEngageTarget(AActor * ActorSensed)
{
	if (ActorSensed != nullptr)
	{
		if (EngageBehavior != EGroundEngageBehavior::Ignore)
		{
			Resting = false;
		}
		switch (EngageTargetBehavior)
		{
		case EEngageTargetBehavior::Fixated:
			//Check you are not already engaged
			if (!Engaged)
			{
				//Set EngagedActor
				EngagedActor = ActorSensed;
				//Start the Aggro Event
				CheckEngageActor2(EngagedActor);
				//Set Engage Parameters
				SetEngageParams();
				GroupEngageBehavior();
			}
			break;
		case EEngageTargetBehavior::Nearest:

			break;
		default:
			break;
		}
	}
}

void AGroundAnimalBase::PerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{

}

void AGroundAnimalBase::TargetPerceptionUpdated(AActor * Actor, FAIStimulus Stimulus)
{
	if (Actor != nullptr)
	{
		if ((!Actor->ActorHasTag(TEXT("abkDead")) && (CanEngage) && (!Dead)))
		{
			//Save actor and stimulus
			SensedActor = Actor;
			switch (CurrentMovementMode)
			{
				case EMoveMode::Walk:
					if (EngageBehavior != EGroundEngageBehavior::Ignore)
					{
						EngagementStart();
						SetEngageTarget(SensedActor);
					}
					else
					{
						GroupEngageBehavior();
					}
					break;
				default:
					break;
			}
		}
	}
}

void AGroundAnimalBase::EngageStuff(AActor* Actor)
{
	if (Actor != nullptr)
	{

		EngagedActor = Actor;
		AIState = EAIState::Engaged;
		UE_LOG(LogTemp, Warning, TEXT("We percept!"));
		/*if ((!Actor->ActorHasTag(TEXT("abkDead")) && (CanEngage) && (!Dead)))
		{
			UE_LOG(LogTemp, Warning, TEXT("We percept!"));
			SensedActor = Actor;
			if (EngageBehavior != EGroundEngageBehavior::Ignore)
			{
				EngagementStart();
				SetEngageTarget(SensedActor);
				AIState = EAIState::Engaged;
			}
		}*/
	}
}

void AGroundAnimalBase::ModifyEngageBehavior(AActor * Actor, AActor*& EngageActor, bool& CanBeEngaged)
{
	bool Engage = true;
	CanBeEngaged = Engage;
	EngageActor = Actor;
}

//////////////////////////////////////////////////////////////
//These custom events are meant to be overriden in a 
//child class to add any functionality we want at the
//start or end of the animal becoming engaged
void AGroundAnimalBase::EngagementStart()
{
	
}

void AGroundAnimalBase::EngagementEnd()
{

}
//////////////////////////////////////////////////////////////

void AGroundAnimalBase::GroupEngageBehavior()
{
	UCompGroup* AnimalComp = FindComponentByClass<UCompGroup>();
	if (AnimalComp != nullptr)
	{
		if (AnimalComp->Active)
		{
			if (AnimalComp->GroupManager != nullptr)
			{
				AnimalComp->GroupManager->SetGroupEngageBehavior(SensedActor);
			}
		}
	}

}

bool AGroundAnimalBase::CheckDestination(FVector RandomLoc)
{
	//UKismetSystemLibrary::SphereTraceMultiForObjects(this,RandomLoc,FVector(RandomLoc.X,RandomLoc.Y,RandomLoc.Z + 0.01),500.0f,)
	return false;
}

void AGroundAnimalBase::PlayAnimation(EAnimType AnimationType)
{
	UE_LOG(LogTemp, Error, TEXT("Animation goes here"));
}

EAIRoamBehavior AGroundAnimalBase::SetRoamBehavior()
{
	if (!CanUseHomeBase)
	{
		if (RoamMode == ERoamMode::Random)
		{
			switch (UKismetMathLibrary::RandomIntegerInRange(0, 4))
			{
			case 0:
				RoamBehavior = EAIRoamBehavior::GoToRandomLocationInNavMesh;
				break;
			case 1:
				RoamBehavior = EAIRoamBehavior::GoToRandomLocationWithinBounds;
				break;
			case 2:
				RoamBehavior = EAIRoamBehavior::GoToRandomWayPoint;
				break;
			case 3:
				RoamBehavior = EAIRoamBehavior::GoToRandomWayPointPath;
				break;
			case 4:
				RoamBehavior = EAIRoamBehavior::GoToNearestPOI;
				break;
			}
		}
		else
		{
			RoamBehavior = OriginalRoamBehavior;
		}
	}
	else
	{
		RoamBehavior = OriginalRoamBehavior;
	}
	if (DebugAnimal.RoamBehavior)
	{
		auto DebugString = UEnum::GetValueAsString<EAIRoamBehavior>(RoamBehavior);
		//UE_LOG(LogTemp, Error, TEXT("Debug String: %s", DebugString);
	}
	return RoamBehavior;
}

void AGroundAnimalBase::SearchForPlayer()
{
	FTimerHandle SearchPlayer;
	GetWorld()->GetTimerManager().SetTimer(SearchPlayer, this,
		&AGroundAnimalBase::SearchForPlayer, Simulation_Details.PlayerCheckFrequency, true);
//	CheckPlayerDistance()
	
}

EGroundEngageBehavior AGroundAnimalBase::DetermineEngageBehavior(EGroundEngageBehavior TagEngageBehavior)
{
	EGroundEngageBehavior Final;
	UCompGroup* AnimalComp = FindComponentByClass<UCompGroup>();
	if (AnimalComp != nullptr)
	{
		if (Engaged)
		{
			if ((TagEngageBehavior == EGroundEngageBehavior::Flee) && (EngageBehavior == EGroundEngageBehavior::Flee))
			{
				Final = EGroundEngageBehavior::Flee;
			}
			else if (EngageBehavior == EGroundEngageBehavior::Attack)
			{
				Final = EGroundEngageBehavior::Attack;
			}
			else
			{
				Final = TagEngageBehavior;
			}
		}
		else
		{
			Final = TagEngageBehavior;
		}
	}
	else
	{
		Final = TagEngageBehavior;
	}
	return Final;
}
