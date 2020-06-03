// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoGroupManager.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GroupManager.h"
#include "CompGroup.h"
#include "Engine/World.h"



// Sets default values
AAutoGroupManager::AAutoGroupManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAutoGroupManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAutoGroupManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAutoGroupManager::CheckGroups()
{
	GetWorld()->GetTimerManager().SetTimer(CheckGroupsTimerHandle, this, &AAutoGroupManager::CheckGroups, CheckFrequency,true);
	ManageGroups();
	if (DebugGroupCreation || DebugLooseAnimals)
	{
		CleanDebugInfo();
	}

}

void AAutoGroupManager::RegisterAnimal(AGroundAnimalBase* ActorRef, EAnimalSex Sex, FText Specie)
{
	int index = -1;
	for (FAutoGroup_SpeciesDetail CurrentSpecies : SpeciesDetail)
	{
		index++;
		if (CurrentSpecies.Species.EqualTo(Specie))
		{
			TArray<AGroundAnimalBase*> MList;
			TArray<AGroundAnimalBase*> FList;
			switch(Sex)
			{
				case EAnimalSex::Male:	
					MList = CurrentSpecies.MaleList;
					MList.Add(ActorRef);
					CurrentSpecies.MaleList = MList;
					SpeciesDetail[index] = CurrentSpecies;
					break;
				case EAnimalSex::Female:
					FList = CurrentSpecies.FemaleList;
					FList.Add(ActorRef);
					CurrentSpecies.FemaleList = FList;
					SpeciesDetail[index] = CurrentSpecies;
					break;
			}
			break;
		}
	}
}

void AAutoGroupManager::ManageGroups()
{
	//Go through all species
	int index = -1;
	for (FAutoGroup_SpeciesDetail CurrentSpecies : SpeciesDetail)
	{
		index++;
		//Save Males and Females for this species
		TArray<AGroundAnimalBase*> Males = CurrentSpecies.MaleList;
		TArray<AGroundAnimalBase*> Females = CurrentSpecies.FemaleList;
		TArray<AGroundAnimalBase*> GroupList;
		int Index = 0;
		//Check that we have the minimum amount of total animals to form a group
		if (Males.Num() + Females.Num() >= FMath::TruncToInt(CurrentSpecies.GroupSize.X))
		{
			bool MalesAvailable = false;
			bool FemalesAvailable = false;
			AGroundAnimalBase* Leader;
			//Check Male Availability
			if (Males.Num() > 0)
			{
				MalesAvailable = true;
			}
			else
			{
				MalesAvailable = false;
			}
			//Check Female availability
			if (Males.Num() > 0)
			{
				FemalesAvailable = true;
			}
			else
			{
				FemalesAvailable = false;
			}
			//Set random group size
			float min = FMath::Clamp(CurrentSpecies.GroupSize.X, 2.0f, 999.0f);
			float max = FMath::Clamp(CurrentSpecies.GroupSize.Y, 2.0f, 999.0f);
			int GroupSize =  FMath::TruncToInt(FMath::RandRange(min, max));
			//Switch on Leader type
			switch (CurrentSpecies.Leader)
			{
			case EAutoGroup_AnimalType::Male:
				if (MalesAvailable)
				{
					Leader = Males[0];
					Males.Remove(Leader);
				}
				break;
			case EAutoGroup_AnimalType::Female:
				if (FemalesAvailable)
				{
					Leader = Females[0];
					Females.Remove(Leader);
				}
				break;
			case EAutoGroup_AnimalType::Random:
				if (FMath::RandBool())
				{
					if (MalesAvailable)
					{
						Leader = Males[0];
						Males.Remove(Leader);
					}
				}
				else
				{
					if (FemalesAvailable)
					{
						Leader = Females[0];
						Females.Remove(Leader);
					}
				}
				break;
			}
			//Populate the rest of the group
			for (int counter = 0; counter < GroupSize-2; counter++)
			{
				switch (CurrentSpecies.GroupComposition)
				{
				case EAutoGroup_AnimalType::Male:
					if (Males.IsValidIndex(0))
					{
						GroupList.Add(Males[0]);
						Males.Remove(Males[0]);
					}
					break;
				case EAutoGroup_AnimalType::Female:
					if (Females.IsValidIndex(0))
					{
						GroupList.Add(Females[0]);
						Females.Remove(Females[0]);
					}
					break;
				case EAutoGroup_AnimalType::Random:
					if (FMath::RandBool())
					{
						if (Males.IsValidIndex(0))
						{
							GroupList.Add(Males[0]);
							Males.Remove(Males[0]);
						}
					}
					else
					{
						if (Females.IsValidIndex(0))
						{
							GroupList.Add(Females[0]);
							Females.Remove(Females[0]);
						}
					}
					break;
				}
			}
			AGroupManager* GroupManager;
			//Is the current group size equal or bigger than then min group size?
			if ((GroupList.Num() + 1) >= FMath::TruncToInt(CurrentSpecies.GroupSize.X))
			{
				//Add leader to group
				GroupList.AddUnique(Leader);
				//Spawn GroupManager for this group
				GroupManager = GetWorld()->SpawnActor<AGroupManager>(CurrentSpecies.GroupManagerSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
				//Deactivate Group Manager
				GroupManager->Active = false;
				//Set Group Manager Settings
				GroupManager->EngageBehaviorMethod = CurrentSpecies.GroupManagerSettings.EngageBehaviorMethod;
				GroupManager->GroupEngageBehavior = CurrentSpecies.GroupManagerSettings.GroupEngageBehavior;
				GroupManager->CanChooseLeader = CurrentSpecies.GroupManagerSettings.ChooseRandomLeader;
				GroupManager->NewLeaderRate = CurrentSpecies.GroupManagerSettings.NewLeaderRate;
				GroupManager->NoDamageByMembers = CurrentSpecies.GroupManagerSettings.NoDamageByMembers;
				//Set Group Manager Settings
				GroupManager->GroupTag = FName(*(GroupManager->GetName()));
				//Set group members and leader
				GroupManager->Group = GroupList;
				GroupManager->GroupLeader = Leader;
				//Go through all group members
				for (AGroundAnimalBase* CurrentMember : GroupList)
				{
					UCompGroup* LeaderComp = Leader->FindComponentByClass<UCompGroup>();
					if (LeaderComp != nullptr)
					{
						LeaderComp->IsGroupLeader = true;
						LeaderComp->CheckLeadership = true;
					}
				}
				if (Leader != nullptr)
				{
					GroupManager->SetGroup();
				}
				//Resize arrays
				CurrentSpecies.MaleList = Males;
				///SpeciesDetail[Index] = CurrentSpecies;
				CurrentSpecies.FemaleList = Females;
				SpeciesDetail[Index] = CurrentSpecies;
				//Increase TotalGroupsCreated
				TotalGroupsCreated++;
				//Add leader to LeaderList
				LeaderList.AddUnique(Leader);
				if (DebugGroupCreation)
				{
					//UE_LOG(LogTemp, Warning, TEXT("%s - GroupSize %d: Leader: %s "), GetName(), GroupList.Num(), Leader->GetName());
				}
				if (Males.Num() + Females.Num() >= FMath::TruncToInt(CurrentSpecies.GroupSize.X))
				{
					ManageGroups();
				}
			}
			else
			{
				//Debug
			}
		}
		else
		{
			//Debug
		}
	}
}

void AAutoGroupManager::CleanDebugInfo()
{
	for (AActor* Leader : LeaderList)
	{
		if (Leader == nullptr)
		{
			LeaderList.Remove(Leader);
		}
	}
}

