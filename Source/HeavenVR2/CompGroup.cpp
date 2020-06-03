// Fill out your copyright notice in the Description page of Project Settings.


#include "CompGroup.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UCompGroup::UCompGroup()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCompGroup::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCompGroup::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCompGroup::SetLeaderName()
{
	if (IsGroupLeader)
	{
		AGroundAnimalBase* Animal = Cast<AGroundAnimalBase>(GetOwner());
		//does stuff in blueprints in the original animal stuff, but not for us
	}
}

void UCompGroup::CheckLeader()
{
	SetLeaderName();
}

AGroundAnimalBase* UCompGroup::GetOwned()
{
	return Cast<AGroundAnimalBase>(GetOwner());

}

void UCompGroup::RegisterWithGroup()
{
	if (Active)
	{
		switch (GroupMode)
		{
		case EGroupMode::Manual:
			EventRegisterWithGroup();
			break;
		case EGroupMode::AutoGroup:
			RegisterWithGroup();
			break;
		case EGroupMode::AutoGroupWithTag:
			RegisterWithAutoGroupTag();
			break;
		}
	}
}

void UCompGroup::EventRegisterWithGroup()
{
	if(GroupManager != nullptr)
	{
		//Add self to group array
		GroupManager->Group.AddUnique(Owner);
		//Is this the Herd Leader?
		if(IsGroupLeader)
		{
			//Set self as Group Leader
			GroupManager->GroupLeader = Owner;
			CheckLeadership = true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(": Comp_Group:  MIssing Group Manager reference!"))
	}
}

void UCompGroup::RegisterWithAutoGroup()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAutoGroupManager::StaticClass(), ActorsFound);
	if (ActorsFound.IsValidIndex(0))
	{
		AAutoGroupManager* MyActor = Cast<AAutoGroupManager>(ActorsFound[0]);
		if (MyActor != nullptr)
		{
			MyActor->RegisterAnimal(Owner, Owner->AnimalDetails.Sex, Owner->AnimalDetails.Species);
		}
		
	}
}

void UCompGroup::RegisterWithAutoGroupTag()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), AutoGroupManagerTag, OutActors);
	if (OutActors.IsValidIndex(0))
	{
		AAutoGroupManager* MyActor = Cast<AAutoGroupManager>(OutActors[0]);
		if (MyActor != nullptr)
		{
			//Register animal with BP_AutoGrouping
			MyActor->RegisterAnimal(Owner, Owner->AnimalDetails.Sex, Owner->AnimalDetails.Species);
		}
	}
}

