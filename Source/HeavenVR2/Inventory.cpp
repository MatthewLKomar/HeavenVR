// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
// Sets default values for this component's properties
UInventory::UInventory()
{

}

bool UInventory::AddItemToInventory(int ID, int Amount)
{
	FItemSetting ItemSettings;
	bool ItemFound = false;
	for (int index = 0; index < InventoryStock.Num(); index++)
	{
		if (InventoryStock[index].ID == ID)
		{
			ItemFound = true;
			InventoryStock[index].Quantity += Amount;
			OnInventoryUpdated.Broadcast();
		}
	}
	if (ItemFound)
	{
		OnInventoryUpdated.Broadcast();
		return true;
	}
	else
	{
		ItemSettings.ID = ID;
		ItemSettings.Quantity = Amount;
		InventoryStock.Add(ItemSettings);
		OnInventoryUpdated.Broadcast();
		return true;
	}

}

bool UInventory::DecrementClue()
{
	if (!(Clues - 1 < 0))
	{
		Clues--;
		return true;
	}
	return false;
}

void UInventory::IncrementClue()
{
	Clues++;
	OnClueAquired.Broadcast();
}

void UInventory::BroadcastInventoryEvents()
{
	OnInventoryUpdated.Broadcast();
}

TArray<int> UInventory::GetInventoryIds()
{
	TArray<int> InventoryIds;
	if (InventoryStock.Num() >= 0)
	{
		for (auto Item : InventoryStock)
		{
			InventoryIds.Add(Item.ID);
		}
	}
	return InventoryIds;
}

bool UInventory::RemoveItemById(int ID)
{
	for (int i = 0; i < InventoryStock.Num(); i++)
	{
		auto Item = InventoryStock[i];
		if (Item.ID == ID)
		{
			InventoryStock.RemoveAt(i);
			return true;
		}
	}
	return false;
}

