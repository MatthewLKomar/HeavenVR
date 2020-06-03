// Fill out your copyright notice in the Description page of Project Settings.


#include "ClueShrine.h"
#include "UObject/ConstructorHelpers.h" //So we can get our table
#include "SimplifiedVRChar.h"
#include "Inventory.h"
#include "Engine/World.h" //We need GetWorld()


// Sets default values
AClueShrine::AClueShrine()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemTableDataObject(TEXT("DataTable'/Game/Inventory/ItemData.ItemData'"));
	if (ItemTableDataObject.Succeeded())
	{
		ItemDataTable = ItemTableDataObject.Object;		
	}
	Shrine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shrine Mesh"));
	Shrine->SetupAttachment(GetRootComponent());

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Shrine);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AClueShrine::OnOverlapBegin);
	//^We need to tell the Engine that we're going to be overllaping things with this collider

	ClueSpot1 = CreateDefaultSubobject<USceneComponent>(TEXT("Clue Spot 1"));
	ClueSpot1->SetupAttachment(GetRootComponent());

	ClueSpot2 = CreateDefaultSubobject<USceneComponent>(TEXT("Clue Spot 2"));
	ClueSpot2->SetupAttachment(GetRootComponent());

	ClueSpot3 = CreateDefaultSubobject<USceneComponent>(TEXT("Clue Spot 3"));
	ClueSpot3->SetupAttachment(GetRootComponent());

	ClueSpot4 = CreateDefaultSubobject<USceneComponent>(TEXT("Clue Spot 4"));
	ClueSpot4->SetupAttachment(GetRootComponent());
}

void AClueShrine::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		auto Player = Cast<ASimplifiedVRChar>(OtherActor);
		if (Player)
		{
			auto PlayerStock = Player->Inventory->InventoryStock;
			
		}
		
	}
}

TArray<int> AClueShrine::FindCluesFromData(UDataTable* Table)
{
	TArray<int> FoundClueIDs;
	if (Table)
	{
		TArray<FName> Rows = Table->GetRowNames();
		for (FName Row : Rows)
		{
			FString ContextString;
			auto Data = Table->FindRow<FItemData>(Row, ContextString, true);
			if (Data)
			{
				if (Data->IsQuestItem)
				{
					FoundClueIDs.Add(Data->ItemID);
				}
			}
		}

	}
	return FoundClueIDs;
}

TArray<FItemSetting> AClueShrine::GetCluesFromPlayer(TArray<FItemSetting> Inventory, UDataTable* Table)
{
	TArray<FItemSetting> Clues;
	TArray<int> ClueIDs = FindCluesFromData(Table);
	if (Inventory.Num() >= 0)
	{
		for (auto Item : Inventory)
		{
			for (int Clue : ClueIDs)
			{
				if (Item.ID == Clue)
				{
					Clues.Add(Item);
				}
			}
		}
	}
	return Clues;
}

//TArray<AItem*> AClueShrine::SpawnCluesToShrine(TArray<FItemSetting> Items, UDataTable* Table)
//{
//	TArray<AItem*> SpawnedItems;
//	for (auto item : Items)
//	{
//		FTransform SpawnLocation;
//		FRotator SpawnRotation;
//		//TSubclassOf<AItem> Thing;
//		//AItem* ItemRef = GetWorld()->SpawnActor<AItem>(Thing, &SpawnLocation, &SpawnRotation);
//		//SpawnedItems.Add(ItemRef);
//	}
//	return SpawnedItems;
//}


