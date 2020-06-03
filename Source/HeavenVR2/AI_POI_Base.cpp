// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_POI_Base.h"

// Sets default values
AAI_POI_Base::AAI_POI_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Root->SetupAttachment(GetRootComponent());

	Bounds = CreateDefaultSubobject<UBoxComponent>(TEXT("Bounds"));
	Bounds->SetupAttachment(Root);
	Bounds->SetWorldScale3D(BoundsScale);

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	TextRender->SetupAttachment(Root);
	TextRender->SetText(Identifier);
	TextRender->SetHiddenInGame(true);

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetupAttachment(Root);
	Billboard->SetWorldScale3D(BillboardScale);

}

// Called when the game starts or when spawned
void AAI_POI_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI_POI_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

