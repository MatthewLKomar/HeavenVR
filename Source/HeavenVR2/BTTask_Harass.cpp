// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Harass.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SimplifiedVRChar.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIC_Base.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

EBTNodeResult::Type UBTTask_Harass::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto AIController = OwnerComp.GetAIOwner();
	Blackboard = OwnerComp.GetBlackboardComponent();

	if (AIController != nullptr)
	{
		AnimalBase = Cast<AGroundAnimalBase>(AIController->GetPawn());
	}
	if (AnimalBase != nullptr)
	{
		//FVector Location;
		//bool Success = LocationMath(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 2000, 500, Location);
		//if (!Success)
		//{
		//	if (DebugLocation)
		//	{
		//		UE_LOG(LogTemp, Error, TEXT("Failed"));
		//	}
		//	AnimalBase->Harass = false;
		//	return EBTNodeResult::Failed;
		//}
		//if (DebugLocation)
		//{
		//	UE_LOG(LogTemp, Error, TEXT("RandomLoc: %s"), *Location.ToString());
		//}
		//Blackboard->SetValueAsVector(TEXT("Vector"), Location);
		AActor* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (Player)
		{
			ASimplifiedVRChar* Char = Cast<ASimplifiedVRChar>(Player);
			if (Char != nullptr && Char->Inventory->Clues > 0)
			{
				AIController->MoveToActor(Player, 50, true, true, true, 0, true);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PLAYER OR CHAR NULL"));
		}
		
	}
	return EBTNodeResult::Failed;
	
}

bool UBTTask_Harass::LocationMath(AActor * ActorHarassing, int DistanceNeededToFollow, float BreathingRoom, FVector & ActorLocation)
{
	if (ActorHarassing)
	{
		FVector ThisLocation = AnimalBase->GetActorLocation();
		FVector TheirLocation = ActorHarassing->GetActorLocation();
		float DistanceBetween = FVector::Dist(ThisLocation, TheirLocation);
		if (DistanceBetween <= DistanceNeededToFollow)
		{
			ActorLocation = FollowActor(ActorHarassing, BreathingRoom);
			return true;
		}
	}
	return false;
}

FVector UBTTask_Harass::FollowActor(AActor * ActorHarassing, float BreathingRoom)
{//Get in the way of the player
	float Direction = DirectionFromActor(ActorHarassing); 
	return GetDirectionLoc(ActorHarassing, BreathingRoom, 0);

	//if (Direction >= 0.5f && Direction <= 1.0f) // If in front
	//{// go right
	//	return GetDirectionLoc(ActorHarassing, BreathingRoom, 2);
	//}
	//else if (Direction >= -1.0f && Direction <= -0.5f)// If in back
	//{//go back
	//	return GetDirectionLoc(ActorHarassing, BreathingRoom, 4);
	//}
	//else
	//{//go left
	//	return GetDirectionLoc(ActorHarassing, BreathingRoom, 3);
	//}
}

FVector UBTTask_Harass::GetDirectionLoc(AActor * ActorHarassing, float BreathingRoom, int Direction)
{
	FVector ThisLoc = AnimalBase->GetActorLocation();
	FVector TheirLoc = ActorHarassing->GetActorLocation();
	switch (Direction)
	{
	case 0: 
	{
		UNavigationSystemV1* NavSys = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
		FNavLocation Result;
		NavSys->GetRandomPointInNavigableRadius(TheirLoc, BreathingRoom, Result);
		return Result.Location;
	}
		
	case 1://Front
		{
			FVector ForwardVector = ActorHarassing->GetActorForwardVector();
			//FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0, 0, AnimalBase->GetActorRotation().Yaw));
			if (DebugLocation)
			{
				UE_LOG(LogTemp, Error, TEXT("Get Direction Loc, Case 1: Front %s"), *(ForwardVector * BreathingRoom).ToString());
			}
			return (ForwardVector * BreathingRoom) + ActorHarassing->GetActorLocation();
		}
	case 2://Right
		{
			FRotator MakeRot = FRotator(0.0f, 0.0f, AnimalBase->GetActorRotation().Yaw);
			FVector RightVector = UKismetMathLibrary::GetRightVector(MakeRot);
			if (DebugLocation)
			{
				UE_LOG(LogTemp, Error, TEXT("Get Direction Loc, Case 2: Right %s"), *(ThisLoc + (RightVector* BreathingRoom)).ToString());
			}
			return ThisLoc + (RightVector* BreathingRoom);
		}
	case 3: //Left
		{
			FRotator MakeRot = FRotator(0.0f, 0.0f, AnimalBase->GetActorRotation().Yaw);
			FVector RightVector = UKismetMathLibrary::GetRightVector(MakeRot);
			FVector LeftVector = FVector(RightVector.X, UKismetMathLibrary::GetRightVector(MakeRot).Y * -1, RightVector.Z);
			if (DebugLocation)
			{
				UE_LOG(LogTemp, Error, TEXT("Get Direction Loc, Case 3: Left %s"), *(ThisLoc + (LeftVector * BreathingRoom)).ToString());
			}
			return ThisLoc + (LeftVector * BreathingRoom);
		}
	default://Back            4 or something else so we don't error
		{
			FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0, 0, AnimalBase->GetActorRotation().Yaw));
			if (DebugLocation)
			{
				UE_LOG(LogTemp, Error, TEXT("Get Direction Loc, Case 4: Back %s"), *((ForwardVector * -1)* BreathingRoom).ToString());
			}
			return (ForwardVector * -1)* BreathingRoom;
		}
	}
}


FVector UBTTask_Harass::GetInTheWay(AActor * ActorHarassing, float BreathingRoom)
{//Get in the way of the player
	return GetDirectionLoc(ActorHarassing, BreathingRoom, 1);
}


float UBTTask_Harass::DirectionFromActor(AActor* Actor)
{//Gets the direction of the other actor between -1.0 (back), 1.0 (front)
	FVector OtherLocation = Actor->GetActorLocation();
	FVector ThisLocation = AnimalBase->GetActorLocation();
	FVector NormalizedVector = OtherLocation - ThisLocation;
	UKismetMathLibrary::Vector_Normalize(NormalizedVector, 0.1f);
	return FVector::DotProduct(AnimalBase->GetActorForwardVector(), NormalizedVector);
}