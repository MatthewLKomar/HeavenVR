// Fill out your copyright notice in the Description page of Project Settings.


#include "GroupManager.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

#include "CompGroup.h"

class UCompGroup;

// Sets default values
AGroupManager::AGroupManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGroupManager::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AGroupManager::BeginPlayStuff, 1.0f, false);

}

// Called every frame
void AGroupManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGroupManager::BeginPlayStuff()
{
	if (Active == true)
	{
		SetGroup();
	}
}

void AGroupManager::SetGroup()
{
	AddGroupTag = true;
	if (ChooseRandomLeader == true)
	{
		ChooseNewLeader();
	}
	if (NoDamageByMembers == true)
	{
		SetNoDamage = true;
	}
	PopulateBehavior();
}

void AGroupManager::LeaveGroup(AGroundAnimalBase* Animal)
{
	if (Animal == GroupLeader)
	{
		SetNewLeader();
	}

}

void AGroupManager::ChooseNewLeader()
{
	LeaderTimerHandle = UKismetSystemLibrary::K2_SetTimer(this, "ChooseNewLeader", NewLeaderRate, true);
	CanChooseLeader = true;
}

void AGroupManager::SetNewLeader()
{
	if (Group.Num() > 1)
	{
		if (GroupLeader != nullptr)
		{
			OldGroupLeader = GroupLeader;
			UCompGroup* OldLeaderComp = GroupLeader->FindComponentByClass<UCompGroup>();
			if (OldLeaderComp != nullptr)
			{
				OldLeaderComp->IsGroupLeader = false;
			}
			OldLeaderComp->IsGroupLeader = false;
			for (int counter = 0; counter < Group.Num(); counter++)
			{
				UCompGroup* NewLeaderComp = Group[counter]->FindComponentByClass<UCompGroup>();
				if (NewLeaderComp != OldLeaderComp)
				{
					NewLeaderComp->IsGroupLeader = true;
					//Reset Old Leader's ref
					OldGroupLeader = nullptr;
					break;
				}
			}
		}
	}
}


AGroundAnimalBase * AGroupManager::GetRandomMember()
{
	//Get random group member
	return Group[FMath::RandRange(0, Group.Num() - 1)];
}

void AGroupManager::SetGroupEngageBehavior(AActor * EngagedActor)
{
	for (AGroundAnimalBase* Member : Group)
	{
		if (Member != nullptr)
		{
			switch (EngageBehaviorMethod)
			{
			case EGroupManager_EngageBehavior::UseGroupEngageBehavior:
			//Set  Engage Behavior to Group Engage Behavior
				Member->EngageBehavior = GroupEngageBehavior;
				Member->OriginalEngageBehavior = GroupEngageBehavior;
				if (GroupEngageBehavior != EGroundEngageBehavior::Ignore)
				{
					Member->SensedActor = EngagedActor;
					Member->SetEngageTarget(EngagedActor);
				}
				break;
			case EGroupManager_EngageBehavior::UseLeaderEngageBehavior:
			//Set  Engage Behavior to Leader's Engage Behavior
				Member->EngageBehavior = GroupLeader->EngageBehavior;
				Member->OriginalEngageBehavior = GroupLeader->EngageBehavior;
				if (GroupLeader->EngageBehavior != EGroundEngageBehavior::Ignore)
				{
					Member->SensedActor = EngagedActor;
					Member->SetEngageTarget(EngagedActor);
				}
				break;
			case EGroupManager_EngageBehavior::USeIndividualEngageBehaviors:
				if (Member->EngageBehavior != EGroundEngageBehavior::Ignore)
				{
					Member->SensedActor = EngagedActor;
					Member->SetEngageTarget(EngagedActor);
				}
				break;
			}
		}
	}
}

void AGroupManager::ChooseLeader()
{
	SetNewLeader();
}

void AGroupManager::SetNoDamageTags()
{
	for (AGroundAnimalBase* Member : Group)
	{
		if (Member != nullptr)
		{
			//Get current values from NoDamageTags array
			TArray<FName> TempArray = Member->AnimalDetails.NoDamageTags;
			//Add the Group Manager name as a tag
			TempArray.Add(FName(*GetName()));
			//Set NoDamageTags array to TempArray to include new tag
			Member->AnimalDetails.NoDamageTags = TempArray;
			//Add an actor tag with the name of the GroupManager
			Member->Tags.Add(FName(*GetName()));
		}
	}
}

void AGroupManager::AddGroupTagToGroup()
{
	for (AGroundAnimalBase* Member : Group)
	{
		if (Member != nullptr)
		{
			//Add the Group Tag to the member of the group
			Member->Tags.Add(GroupTag);
		}
	}
}

void AGroupManager::PopulateBehavior()
{
	for (AGroundAnimalBase* Member : Group)
	{
		if (Member != nullptr)
		{
			switch (EngageBehaviorMethod)
			{
			case EGroupManager_EngageBehavior::UseGroupEngageBehavior:
				Member->EngageBehavior = GroupEngageBehavior;
				Member->OriginalEngageBehavior = GroupEngageBehavior;
				break;
			case EGroupManager_EngageBehavior::UseLeaderEngageBehavior:
				Member->EngageBehavior = GroupLeader->EngageBehavior;
				Member->OriginalEngageBehavior = GroupLeader->EngageBehavior;
				break;
			case EGroupManager_EngageBehavior::USeIndividualEngageBehaviors:
				break;
			}
		}
	}
}
