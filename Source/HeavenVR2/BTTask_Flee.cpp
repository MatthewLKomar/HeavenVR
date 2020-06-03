// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Flee.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "AIC_Base.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

EBTNodeResult::Type UBTTask_Flee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto AIController = OwnerComp.GetAIOwner();
	Blackboard = OwnerComp.GetBlackboardComponent();

	if (AIController != nullptr)
	{
		AnimalBase = Cast<AGroundAnimalBase>(AIController->GetPawn());
	}
	if (AnimalBase != nullptr)
	{
		if (AnimalBase->RunAway == false)
		{
			return EBTNodeResult::Failed;
		}
		//We should check if we're far enough from the enemy. If we are, we should stop fleeing and go back to our normal tasks.
		AActor* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (Player)
		{
			FVector PlayerLocation = LocationMath(Player, 1000, 5000, 1000);
			if (DebugLocation)
			{
				UE_LOG(LogTemp, Error, TEXT("RandomLoc: %s"), *PlayerLocation.ToString());
			}
			SetRunAtMaxSpeed();
			Blackboard->SetValueAsVector(TEXT("Vector"), PlayerLocation);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PLAYER NULL"));
		}
	}
	return EBTNodeResult::Failed;
}

FVector UBTTask_Flee::LocationMath(AActor* ActorFleeingFrom,int DistanceMin, int DistanceMax, int Height)
{//Calculating where to walk in relationship to direction of the ActorFleeingFrom and where we are
	FVector WhereToGo;
	//Math to find which direction player is facing explained by: ausernottaken  @ 
	//https://tinyurl.com/ycjfwoz5
	

	float Direction = DirectionFromActor(ActorFleeingFrom);
	//We need to get a reference to our Navigation System so we do it through casting
	UNavigationSystemV1* NavSys = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
	FNavLocation NavPoint; //This will be our return value for where we're going to go


	if (Direction >= .6 && Direction <= -0.6)
	{
		float Distance = DistanceMax;
		FVector TempLocation = PointMath(AnimalBase->GetActorLocation(), Distance, Height);
		//Discord Unreal Slackers user ZLo informed me about the Project Point to Navigation function
			//We're using this function because my algorithm picks a random point in an area, that's may not be on the nav mesh
				//This function places it on the nav mesh.
		bool Success = NavSys->ProjectPointToNavigation(TempLocation, NavPoint, FVector(Distance, Distance, Distance));
		if (Success)
		{
			WhereToGo = NavPoint.Location;
		}
		if (DebugLocation)
		{
			UE_LOG(LogTemp, Warning, TEXT("Direction: %f, location: %s"), Direction, *NavPoint.Location.ToString());
		}

	}
	else
	{
		float Distance = DistanceMax;
		FVector TempLocation = PointMath(AnimalBase->GetActorLocation(), Distance, Height);
		bool Success = NavSys->ProjectPointToNavigation(TempLocation, NavPoint, FVector(Distance,Distance,Distance));
		if (Success)
		{
			WhereToGo = NavPoint.Location;
		}
		else
		{
			NavSys->GetRandomPointInNavigableRadius(TempLocation, Distance, NavPoint);
			WhereToGo = NavPoint.Location;
		}
		if (DebugLocation)
		{
			UE_LOG(LogTemp, Warning, TEXT("Direction: %f, location: %s"), Direction, *NavPoint.Location.ToString());
		}
	}
	return WhereToGo;
}

float UBTTask_Flee::DirectionFromActor(AActor* Actor)
{//Gets the direction of the other actor between -1.0 (back), 1.0 (front)
	FVector OtherLocation = Actor->GetActorLocation();
	FVector ThisLocation = AnimalBase->GetActorLocation();
	FVector NormalizedVector = OtherLocation - ThisLocation;
	UKismetMathLibrary::Vector_Normalize(NormalizedVector, 0.1f);
	return FVector::DotProduct(AnimalBase->GetActorForwardVector(), NormalizedVector);
}

FVector UBTTask_Flee::PointMath(FVector StartLoc,int Distance, int Height)
{//Generates a point depending on the distance away from the animal
	
	FRotator MakeRot = FRotator(0.0f, 0.0f, AnimalBase->GetActorRotation().Yaw);
	FVector RightVector = UKismetMathLibrary::GetRightVector(MakeRot);
	// Corner 1 
	FVector Corner1; // (+x,+y)
	Corner1 = StartLoc + (RightVector* Distance);
	// Corner 4
	FVector Corner4; // (-x,+y)
	FVector LeftVector = FVector(RightVector.X, UKismetMathLibrary::GetRightVector(MakeRot).Y * -1, RightVector.Z);
	Corner4 = StartLoc + (LeftVector * Distance);
	//Bounding Box goes here
	
	FVector Origin = FVector((Corner1.X + Corner4.X )/ 2, (Corner1.Y + Corner4.Y )/ 2, (Corner1.Z + Corner4.Z) / 2);
	FVector Point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Corner4);
	
	return Point;
}

void UBTTask_Flee::SetRunAtMaxSpeed()
{ //We're running at max speed away from the engager
	UCharacterMovementComponent* CharacterMovement = AnimalBase->GetCharacterMovement();

	FVector2D LocRange = AnimalBase->BehaviorLocation.WaitAtLocationRange;
	FVector2D AccelerationRange = AnimalBase->RandomMovement.AccelerationRange;
	AnimalBase->GetCharacterMovement()->MaxWalkSpeed =
		CharacterMovement->MaxWalkSpeed * LocRange.Y;
	AnimalBase->GetCharacterMovement()->MaxAcceleration =
		CharacterMovement->MaxAcceleration *  AccelerationRange.Y;
}

void UBTTask_Flee::DelayHolderFunction()
{
	//This doesn't really do anything 
	//it just serves as a shell for something we call as a delay
	//if we call a delay that is!
}