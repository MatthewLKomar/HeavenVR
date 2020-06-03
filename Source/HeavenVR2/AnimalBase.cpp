// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalBase.h"

// Sets default values
AAnimalBase::AAnimalBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAnimalBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnimalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAnimalBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AAnimalBase::CanTakeDamage(AActor * CauserOfDamage)
{
	for (FName DamageTag : AnimalDetails.NoDamageTags)
	{
		//Is one of the No Damage Tags found on the Damage Causer?
		if (CauserOfDamage->Tags.Contains(DamageTag))
		{
			return false;
		}
		else {
			return true;
		}
	}
	return true;
}

