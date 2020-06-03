// Fill out your copyright notice in the Description page of Project Settings.
//Blueprint Use:
/*
This represents the area where the AI is allowed to move while going to a random location.
The AI will pick random vectors inside this volume.
Use the BoundScale variable to size the volume correctly
*/

#include "AI_BoundingBox.h"

// Sets default values
AAI_BoundingBox::AAI_BoundingBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene")); 
	Root->SetupAttachment(GetRootComponent()); 

	Bounds = CreateDefaultSubobject<UBoxComponent>(TEXT("Bounds"));
	Bounds->SetupAttachment(Root);
	Bounds->SetWorldScale3D(BoundsScale);

	Marker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Marker"));
	Marker->SetupAttachment(Bounds);
	Marker->SetWorldScale3D(BoundsScale*0.625);
	Marker->SetVisibility(bMarkerVisibleInEditor);
	Marker->SetHiddenInGame(bMarkerHiddenInGame);

	PathName = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	PathName->SetupAttachment(Root);
	PathName->SetWorldScale3D(TextScale);


	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetupAttachment(Root);
	Billboard->SetWorldScale3D(BillboardScale);

}

// Called when the game starts or when spawned
void AAI_BoundingBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI_BoundingBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

