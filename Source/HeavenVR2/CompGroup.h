// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Animal_Enums.h"
#include "AutoGroupManager.h"
#include "GroupManager.h"
#include "GroundAnimalBase.h"
#include "CompGroup.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEAVENVR2_API UCompGroup : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCompGroup();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
		void SetLeaderName();//useless delete when done

	UFUNCTION()
		void CheckLeader();
	UFUNCTION()
		AGroundAnimalBase* GetOwned();
	UFUNCTION()
		void RegisterWithGroup();
	UFUNCTION()
		void EventRegisterWithGroup();
	UFUNCTION()
		void RegisterWithAutoGroup();
	UFUNCTION()
		void RegisterWithAutoGroupTag();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		bool Active = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		EGroupMode GroupMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		AGroupManager* GroupManager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		bool IsGroupLeader = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		float MaxLeaderDistance = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		FName AutoGroupManagerTag = TEXT("AutoGroup1");
	UPROPERTY(BlueprintReadWrite)
		AGroundAnimalBase* Owner;
	UPROPERTY(BlueprintReadWrite)
		bool PartOfAGroup = false;
	UPROPERTY(BlueprintReadWrite)
		bool CheckLeadership = false;
private:
	TArray<AActor*> ActorsFound;

		
};
