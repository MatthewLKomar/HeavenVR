// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundAnimalBase.h"
#include "Animal_Enums.h"
#include "Animal_Structs.h"

#include "AutoGroupManager.generated.h"

/*
This Blueprint is used form groups of AI that behave in a cohesive manner. 
The group has a leader and shares engage status among all members.
This allows the group to share information among each other and assigns a new Leader if the old Leader dies.
*/
UCLASS()
class HEAVENVR2_API AAutoGroupManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAutoGroupManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public: 
	UPROPERTY(BlueprintReadWrite, Category = Setup)
		FTimerHandle CheckGroupsTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		bool Active = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		float CheckFrequency = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		TArray<FAutoGroup_SpeciesDetail> SpeciesDetail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName UniqueTag = TEXT("AutoGroup1");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		bool DebugGroupCreation = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		bool DebugLooseAnimals = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		int TotalGroupsCreated = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		TArray<AActor*> LeaderList;
	UPROPERTY(BlueprintReadWrite)
		FTimerHandle CheckHandler;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void CheckGroups();
	UFUNCTION()
		void RegisterAnimal(AGroundAnimalBase* ActorRef, EAnimalSex Sex, FText Specie);
	UFUNCTION()
		void ManageGroups();
	UFUNCTION()
		void CleanDebugInfo();

};
