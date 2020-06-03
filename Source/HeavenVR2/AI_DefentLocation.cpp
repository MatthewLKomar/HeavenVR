// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_DefentLocation.h"
#include "Animal_Enums.h"
//#include "Animal_Structs.h"


AAI_DefentLocation::AAI_DefentLocation() {

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(GetRootComponent());
	Trigger->SetWorldScale3D(TriggerScale);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AAI_DefentLocation::OnOverlapBegin);

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	TextRender->SetupAttachment(GetRootComponent());
	TextRender->SetText(FText::FromString("Defend"));
	TextRender->SetHiddenInGame(true);
}

void AAI_DefentLocation::CheckActor(AActor* Actor)
{
	for (FName tag : Actor->Tags)
	{
		if (ActorTags.Contains(tag))
		{
			CallAnimals();
			break;
		}
	}
	
}

void AAI_DefentLocation::CallAnimals()
{
	for (AGroundAnimalBase* Animal : GroundAnimals)
	{
		Animal->EngageBehavior = EGroundEngageBehavior::Defend;
		Animal->DefenseState = EDefenseState::GoingToDefenseLocation;
		Animal->EngagedActor = OverlappedActor;
		Animal->SetEngageParams();
	
	}
}

void AAI_DefentLocation::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlappedActor = OtherActor;
	if (bActive == true) {
		CheckActor(OverlappedActor);
	}
}

void AAI_DefentLocation::BeginPlay()
{
	Super::BeginPlay();
	ActorTags.Add(TEXT("abkAnimal"));
	ActorTags.Add(TEXT("abkPlayer"));
}
