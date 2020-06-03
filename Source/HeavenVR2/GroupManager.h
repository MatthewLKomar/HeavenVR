// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundAnimalBase.h"
#include "GroupManager.generated.h"

UCLASS()
class HEAVENVR2_API AGroupManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGroupManager();

public:
	UPROPERTY(BlueprintReadWrite, Category = Setup)
	FTimerHandle FuzeTimerHandle;
	UPROPERTY(BlueprintReadWrite, Category = Setup)
	TArray<AGroundAnimalBase*> Group;
	UPROPERTY(BlueprintReadWrite, Category = Setup)
		AGroundAnimalBase* GroupLeader;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		bool Active = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		EGroupManager_EngageBehavior EngageBehaviorMethod = EGroupManager_EngageBehavior::UseGroupEngageBehavior;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		EGroundEngageBehavior GroupEngageBehavior = EGroundEngageBehavior::Ignore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		bool ChooseRandomLeader = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		float NewLeaderRate = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		bool NoDamageByMembers = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName GroupTag = TEXT("None");
	UPROPERTY(BlueprintReadWrite)
		FTimerHandle LeaderTimerHandle;
	UPROPERTY(BlueprintReadWrite)
		AGroundAnimalBase* OldGroupLeader;
	UPROPERTY(BlueprintReadWrite)
		bool CanChooseLeader = false;
	UPROPERTY(BlueprintReadWrite)
		bool SetNoDamage = false;
	UPROPERTY(BlueprintReadWrite)
		bool AddGroupTag = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SetGroup();
	UFUNCTION()
		void LeaveGroup(AGroundAnimalBase* Animal);
	UFUNCTION()
		void ChooseNewLeader();
	UFUNCTION()
		void SetNewLeader();
	UFUNCTION()
		AGroundAnimalBase* GetRandomMember();
	UFUNCTION()
		void SetGroupEngageBehavior(AActor* EngagedActor);
	UFUNCTION()
		void ChooseLeader();
	UFUNCTION()
		void SetNoDamageTags();
	UFUNCTION()
		void AddGroupTagToGroup();
	UFUNCTION()
		void PopulateBehavior();
private:
	UFUNCTION()
		void BeginPlayStuff();
	

};
