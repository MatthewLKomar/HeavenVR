// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "UObject/ConstructorHelpers.h"
#include "ItemSettings.h"


//BP Overidable
AItem::AItem()
{
	//Load inventory data table
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemTableDataObject(TEXT("DataTable'/Game/Inventory/ItemData.ItemData'"));
	if (ItemTableDataObject.Succeeded())
	{
		ItemDataTable = ItemTableDataObject.Object;
		CreateItem();
	}

}


void AItem::PickUp(int & ID, bool & QuestItem, int & AmountOfItems)
{
	ID = ItemID;
	QuestItem = IsQuestItem;
	AmountOfItems = Amount;
}

bool AItem::Drop(int Identifier)
{
	ItemID = Identifier;
	CreateItem();

	//{
		//return true;
	//}
	return true	;
}

bool AItem::CreateItem()
{
	bool FoundItem = false;
	if (ItemDataTable)
	{
		TArray<FName> Rows = ItemDataTable->GetRowNames();
		for (FName Row : Rows)
		{
			FString ContextString;
			auto Data = ItemDataTable->FindRow<FItemData>(Row, ContextString, true);
			if (Data)
			{
				if (Data->ItemID == ItemID)
				{
					FoundItem = true;
					ThisMesh = Data->Mesh;
					ItemName = Data->ItemName;
					IsQuestItem = Data->IsQuestItem;
					IsWeapon = Data->IsWeapon;
					ItemCreated.Broadcast();
					return true;
				}
			}
		}
	}
	else if (!ItemDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("The data table doesn't exist in the %s item!"));
		return false;
	}
	UE_LOG(LogTemp, Error, TEXT("Item ID %d doesn't exist!"), ItemID);
	return false;
}