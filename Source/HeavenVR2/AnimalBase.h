// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animal_Structs.h"

#include "AnimalBase.generated.h"

UCLASS()
class HEAVENVR2_API AAnimalBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnimalBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public: 
	UPROPERTY(BlueprintReadWrite, Category = SetupGeneral)
		TArray<FName> ActorTags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupGeneral)
		FAnimalBase_SimDetails Simulation_Details; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupGeneral)
		FAnimalBase_AnimalDetails AnimalDetails;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupGeneral)
		FAnimalBase_AnimalDeath Death_Details;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = SetupGeneral)
		TArray<FName> AdditionalTags;

	UPROPERTY(BlueprintReadWrite, Category = SetupAnimalDetails)
		float CurrentHP = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = State)
		bool Engaged = false;
	UPROPERTY(BlueprintReadWrite, Category = State)
		bool Resting = false;
	UPROPERTY(BlueprintReadWrite, Category = State)
		bool Awake = true;
	UPROPERTY(BlueprintReadWrite, Category = State)
		bool Dead = false;
	UPROPERTY(BlueprintReadWrite, Category = State)
		bool Attacking = false;
	UPROPERTY(BlueprintReadWrite, Category = State)
		bool TakeDamage = true;
	UPROPERTY(BlueprintReadWrite, Category = State)
		bool breeeding = false;
	UPROPERTY(BlueprintReadWrite, Category = State)
		bool Active = true;
	UPROPERTY(BlueprintReadWrite, Category = Setup)
		bool RunAway = false;
	UPROPERTY(BlueprintReadWrite, Category = State)
		AActor* DamageCauser;
	UPROPERTY(BlueprintReadWrite, Category = State)
		float DamageFrequency = 0.1;
		//^Min frequency animals can take damage

	UPROPERTY(BlueprintReadWrite)
		float DamageAmount = 0.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
		bool CanTakeDamage(AActor * CauserOfDamage);

};
