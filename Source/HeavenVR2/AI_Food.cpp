// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Food.h"

// Sets default values
AAI_Food::AAI_Food()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAI_Food::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI_Food::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

