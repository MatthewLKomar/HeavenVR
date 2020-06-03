// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetAIState.h"
#include "GroundAnimalBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Perception/AISense_Damage.h"
#include "AIController.h"
#include "CommonFunctions.h"
#include "CompGroup.h"
#include "GameFramework/CharacterMovementComponent.h"



UBTService_SetAIState::UBTService_SetAIState()
{
	bCreateNodeInstance = true;
}

void UBTService_SetAIState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	AIController = OwnerComp.GetAIOwner();	
	Blackboard = OwnerComp.GetBlackboardComponent();
	if (AIController != nullptr)
	{
		AnimalBase = Cast<AGroundAnimalBase>(AIController->GetPawn());
	}
	if (AIController && Blackboard && AnimalBase)
	{
		if (DoOnce)
		{
			DoOnce = false;
			//Save distance to activate
			RadiusToActivate = AnimalBase->Simulation_Details.RadiusToActivate;
			//Set StopForEngageAnim
			StopForEngageAnim = AnimalBase->StopForEngageAnim;
			//Set Blackboard value for AnimalRunMode
			Blackboard->SetValueAsEnum(RunMode, (uint8)AnimalBase->Simulation_Details.AIRunMode);
			//Get Inactive Options
			InactiveOptions = AnimalBase->Simulation_Details.InactiveOptions;
			//Set Predictive Movement
			Blackboard->SetValueAsBool(FeedingBehavior, AnimalBase->Simulation_Details.bUsePredictiveMovement);
			//Set Feeding Behavior
			Blackboard->SetValueAsEnum(FeedingBehavior, (uint8)AnimalBase->BehaviorDetails.FeedingBehavior);
			//Set paramters for Movement / Obstacle Check
			FGroundAnimal_MovementObstruction MoveObstruct = AnimalBase->MovementObstruction;
			CheckMovementObstacles = MoveObstruct.bActive;
			ObstacleCheckFrequency = MoveObstruct.CheckFrequency;
			MinStuckDistance = MoveObstruct.MinimumStuckDistance;
			MaxStuckTimes = MoveObstruct.MaxObstructedChecks;
			CollisionReductionPercent = MoveObstruct.CollisionReductionPercent;
			NewCollisionTime = MoveObstruct.ModifiedCollisionTime;
			RelocationChecks = MoveObstruct.MaxChecksForRelocation;
			DebugMovementObstacles = MoveObstruct.bDebug;
			//Switch on EAIRoamBehavior to set our RoamBehavior key
			switch (AnimalBase->RoamBehavior)
			{
			case EAIRoamBehavior::StayInPlace:
				Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::StayInPlace);
				break;
			case EAIRoamBehavior::GoToRandomLocationInNavMesh:
				Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoToRandomLocationInNavMesh);
				break;
			case EAIRoamBehavior::GoToRandomLocationWithinBounds:
				Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoToRandomLocationWithinBounds);
				break;
			case EAIRoamBehavior::GoToRandomWayPoint:
				Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoToRandomWayPoint);
				break;
			case EAIRoamBehavior::FollowWayPointPath:
				Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::FollowWayPointPath);
				break;
			case EAIRoamBehavior::GoToNearestPOI:
				Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoToNearestPOI);
				break;
			default:
				Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoTOHomeBase);
				break;
			}

		}
		DetermineAIState();
		switch (AIState)
		{
		case EAIState::Inactive:
			//Check that the biggest need is rest
			if (AnimalBase->BiggestNeed == EGroundNaturalBehavior::Rest)
			{
				//Check if animal has Day Night Cycle component and it wants to rest while inactive
			}
			break;
		case EAIState::Active: //		case EAIState::Active:
			SetBiggestNeed();
			DoOnce = true;
			break;
		case EAIState::Engaged: //		case EAIState::Engaged:
			SetEngageBehavior();
			if (DoOnce2)
			{
				DoOnce2 = false;
				if (StopForEngageAnim)
				{
					AnimalBase->GetCharacterMovement()->bOrientRotationToMovement = false;
					AnimalBase->GetCharacterMovement()->StopMovementImmediately();
					AnimalBase->PlayAnimation(EAnimType::Engage);
					//Wait for the engage animation duration and set walk speed to 0
					auto AnimMontage = AnimalBase->GetCurrentMontage();
					if (AnimMontage)
					{
						AnimalBase->GetCharacterMovement()->MaxWalkSpeed = 0.0f;
						float Duration = AnimMontage->GetPlayLength() / AnimalBase->CurrentAnimation.AnimationPlayrate;
						GetWorld()->GetTimerManager().SetTimer(Delayer, this,
							&UBTService_SetAIState::DelayHolderFunction, Duration, false);
						AnimalBase->GetCharacterMovement()->MaxWalkSpeed = AnimalBase->BehaviorDetails.EngageMaxWalkSpeed;
						AnimalBase->StopAnimMontage();
						AnimalBase->GetCharacterMovement()->bOrientRotationToMovement = true;

					}

				}
				else
				{
					AnimalBase->PlayAnimation(EAnimType::Engage);
					//Wait for the engage animation duration
					auto AnimMontage = AnimalBase->GetCurrentMontage();
					if (AnimMontage)
					{
						float Duration = (AnimMontage->GetPlayLength()) / (AnimalBase->CurrentAnimation.AnimationPlayrate);
						GetWorld()->GetTimerManager().SetTimer(Delayer, this,
							&UBTService_SetAIState::DelayHolderFunction, Duration, false);
						AnimalBase->StopAnimMontage();
					}
				}
				
			}
			break;
		default:
			break;
		}
	}
	Blackboard->SetValueAsBool(RunAway, AnimalBase->RunAway);
	Blackboard->SetValueAsBool(Harass, AnimalBase->Harass);
}


void UBTService_SetAIState::SetBiggestNeed()
{
	auto BigNeed = AnimalBase->BiggestNeed;
	switch (BigNeed)
	{
	case EGroundNaturalBehavior::Eat:
		Blackboard->SetValueAsEnum(BiggestNeed, (uint8)EGroundNaturalBehavior::Eat);
		break;
	case EGroundNaturalBehavior::Drink:
		Blackboard->SetValueAsEnum(BiggestNeed, (uint8)EGroundNaturalBehavior::Drink);
		break;
	case EGroundNaturalBehavior::Breed:
		Blackboard->SetValueAsEnum(BiggestNeed, (uint8)EGroundNaturalBehavior::Breed);
		break;
	case EGroundNaturalBehavior::Roam:
		Blackboard->SetValueAsEnum(BiggestNeed, (uint8)EGroundNaturalBehavior::Roam);
		SetNextBehaviorInBlackboard(AnimalBase->RoamBehavior);
		break;
	case EGroundNaturalBehavior::Rest:
		Blackboard->SetValueAsEnum(BiggestNeed, (uint8)EGroundNaturalBehavior::Rest);
		break;
	case EGroundNaturalBehavior::FollowParent:
		Blackboard->SetValueAsEnum(BiggestNeed, (uint8)EGroundNaturalBehavior::FollowParent);
		break;
	case EGroundNaturalBehavior::FollowLeader:
		Blackboard->SetValueAsEnum(BiggestNeed, (uint8)EGroundNaturalBehavior::FollowLeader);
		break;
	case EGroundNaturalBehavior::CustomNeed:
		break;
	default:
		break;
	}
	Blackboard->SetValueAsBool(Resting, false);
}

void UBTService_SetAIState::SetEngageBehavior()
{
	auto EngageBehav = AnimalBase->EngageBehavior;
	switch (EngageBehav)
	{
	case EGroundEngageBehavior::Ignore:
		Blackboard->SetValueAsEnum(EngageBehavior, (uint8)EGroundEngageBehavior::Ignore);
		break;
	case EGroundEngageBehavior::Flee:
		Blackboard->SetValueAsEnum(EngageBehavior, (uint8)EGroundEngageBehavior::Flee);
		break;
	case EGroundEngageBehavior::TryToHide:
		Blackboard->SetValueAsEnum(EngageBehavior, (uint8)EGroundEngageBehavior::TryToHide);
		break;
	case EGroundEngageBehavior::Defend:
		Blackboard->SetValueAsEnum(EngageBehavior, (uint8)EGroundEngageBehavior::Defend);
		break;
	case EGroundEngageBehavior::Attack:
		Blackboard->SetValueAsEnum(EngageBehavior, (uint8)EGroundEngageBehavior::Attack);
		break;
	default:
		break;
	}

}

void UBTService_SetAIState::SetNextBehaviorInBlackboard(EAIRoamBehavior Selection)
{
	switch (Selection)
	{
	case EAIRoamBehavior::StayInPlace:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::StayInPlace);
		break;
	case EAIRoamBehavior::GoToRandomLocationInNavMesh:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoToRandomLocationInNavMesh);
		break;
	case EAIRoamBehavior::GoToRandomLocationWithinBounds:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoToRandomLocationWithinBounds);
		break;
	case EAIRoamBehavior::GoToRandomWayPoint:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoToRandomWayPoint);
		break;
	case EAIRoamBehavior::GoToRandomWayPointPath:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoToRandomWayPointPath);
		break;
	case EAIRoamBehavior::FollowWayPointPath:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::FollowWayPointPath);
		break;
	case EAIRoamBehavior::GoToNearestPOI:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoToNearestPOI);
		break;
	case EAIRoamBehavior::GoTOHomeBase:
		Blackboard->SetValueAsEnum(RoamBehavior, (uint8)EAIRoamBehavior::GoTOHomeBase);
		break;
	default:
		break;
	}
}
void UBTService_SetAIState::DelayHolderFunction()
{
	//This doesn't really do anything 
}

void UBTService_SetAIState::CheckMovement()
{
	GetWorld()->GetTimerManager().SetTimer(ObstacleCheckHandler, this,
		&UBTService_SetAIState::CheckMovement, AnimalBase->Simulation_Details.PlayerCheckFrequency, true);
	GetWorld()->GetTimerManager().SetTimer(Delayer, this,
		&UBTService_SetAIState::DelayHolderFunction, UKismetMathLibrary::RandomFloatInRange(0.0f, 2.0f), false);
	/*FoundPlayer = CheckPlayerDist(AnimalBase->GetActorLocation(), RadiusToActivate,
		AnimalBase->DebugAnimal.PlayerProximityCheck, 1.0f);*/
	SetInactiveOptions();
}

void UBTService_SetAIState::CheckPlayerDistance()
{
	GetWorld()->GetTimerManager().SetTimer(ObstacleCheckHandler, this,
		&UBTService_SetAIState::CheckPlayerDistance, ObstacleCheckFrequency, true);
	CheckMovement();
}



void UBTService_SetAIState::SetNewCollision()
{

}

void UBTService_SetAIState::Disengage()
{

}

void UBTService_SetAIState::SetInactiveOptions()
{
	//Did we find the Player?
	if (FoundPlayer) 
	{
		PlayerFound();
	}
	else
	{
		NoPlayerFound();
	}
}

void UBTService_SetAIState::PlayerFound()
{
	//Is Animal Resting?
	if (AnimalBase->Resting)
	{
		AnimalBase->BiggestNeed = EGroundNaturalBehavior::Rest;
	}
	//Hide ANimal
	if (InactiveOptions.bMakeVisibleWhenInactive)
	{
		AnimalBase->SetActorHiddenInGame(false);
	}
	if (InactiveOptions.bDisableCollisionWhileInactive)
	{
		AnimalBase->SetActorEnableCollision(true);
	}
	if (InactiveOptions.StopActorTick)
	{
		AnimalBase->SetActorTickEnabled(true);
	}
	if (InactiveOptions.DisableAllComponents_aggresive)
	{
		SetAllComponentsOn(true);
	}
	if (InactiveOptions.DisableAIController)
	{
		SetAIControllerOn(true);
	}
}

void UBTService_SetAIState::SetAllComponentsOn(bool SetOn)
{
	//TODO SetAllComponentsOn
}
void UBTService_SetAIState::SetAIControllerOn(bool SetOn)
{
	//TODO SetAIControllerOn

}
void UBTService_SetAIState::NoPlayerFound()
{
	//Despawn animal
	if (InactiveOptions.DespawnWhenInactive)
	{
		//PopulationControl  = (Get component by class )
		//if (IsValid((PopulationControl)){}
			// if (DoOnce){}
	}
	if (AnimalBase)
	{
		if (InactiveOptions.bMakeVisibleWhenInactive)
		{
			AnimalBase->SetActorHiddenInGame(true);
		}
		if (InactiveOptions.bDisableCollisionWhileInactive)
		{
			AnimalBase->GetCapsuleComponent()->SetEnableGravity(false);
			AnimalBase->SetActorEnableCollision(true);
		}
		if (InactiveOptions.StopActorTick)
		{
			AnimalBase->SetActorTickEnabled(false);
		}
		if (InactiveOptions.DisableAllComponents_aggresive)
		{
			SetAllComponentsOn(false);
		}
		if (InactiveOptions.DisableAIController)
		{
			SetAIControllerOn(false);
		}
		if (InactiveOptions.StopAILogic)
		{
			AnimalBase->SearchForPlayer();
		}
	}
}

void UBTService_SetAIState::DetermineAIState()
{
	if (!AnimalBase->Dead)
	{
		EAIRunMode AnimalRunMode = AnimalBase->Simulation_Details.AIRunMode;
		switch (AnimalRunMode)
		{
		case EAIRunMode::RunOnProximity:
			if (FoundPlayer)
			{
				AnimalBase->Active = true;
				DetermineAIState2();
			}
			else
			{
				AnimalBase->Active = false;
				AIState = EAIState::Inactive;
			}
			break;
		case EAIRunMode::AlwaysRun:
			DetermineAIState2();
			break;
		case EAIRunMode::UseActivationManager:
			if (AnimalBase->Active)
			{
				DetermineAIState2();
			}
			else
			{
				AIState = EAIState::Inactive;
			}
			break;
		}

	}
	Blackboard->SetValueAsEnum(State, (uint8)AIState);
}

void UBTService_SetAIState::DetermineAIState2()
{
	UCompGroup* CompGroup = (UCompGroup*)AnimalBase->GetComponentByClass(TSubclassOf<UCompGroup>());
	//Are we NOT in a group?
	if (IsValid(CompGroup) == false)
	{
		if (AnimalBase->Engaged)
		{
			AIState = EAIState::Engaged;
		}
		else
		{
			AIState = EAIState::Active;
		}
	}
	//Is component Comp_Group NOT active?
	else if (!CompGroup->Active)
	{
		if (AnimalBase->Engaged)
		{
			DetermineAIState3();
		}
		else
		{
			AIState = EAIState::Active;
		}
	}
	else if (!CompGroup->GroupManager)
	{
		if (AnimalBase->Engaged)
		{
			DetermineAIState3();
		}
		else
		{
			AIState = EAIState::Active;
		}
	}
	//Are we the leader of the group? If not, be part of group
	else if (CompGroup->IsGroupLeader)
	{
		DetermineAIState3();
	}
	//Check to see if Pawn is Engaged
	else if (AnimalBase->Engaged)
	{
		DetermineAIState3();
	}
	else
	{
		AIState = EAIState::Active;
		SetBiggestNeedToFollowLeader();
	}
	//Did we find Bait around?
	if (Blackboard->GetValueAsBool(FoundBait))
	{
		AIState = EAIState::FoundBait;
	}
	
}
void UBTService_SetAIState::SetBiggestNeedToFollowLeader()
{
	if (AnimalBase->BiggestNeed == EGroundNaturalBehavior::Roam)
	{
		AnimalBase->BiggestNeed = EGroundNaturalBehavior::FollowLeader;
	}
}

void UBTService_SetAIState::DetermineAIState3()
{
	AIState = EAIState::Engaged;
	if (AnimalBase->EngageBehavior == EGroundEngageBehavior::Defend)
	{
		Blackboard->SetValueAsEnum(DefenseState, (uint8)AnimalBase->DefenseState);
	}
}
