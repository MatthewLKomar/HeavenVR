// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemSettings.h"
#include "Inventory.generated.h"


//Blueprint will bind to this to update the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
//Bind to classes that need to know if the player took clues
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClueAquired);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEAVENVR2_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

public:	

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool AddItemToInventory(int ID, int Amount);
	UFUNCTION(BlueprintCallable, Category = "Clue")
		bool DecrementClue();
	UFUNCTION(BlueprintCallable, Category = "Clue")
		void IncrementClue();
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FOnInventoryUpdated OnInventoryUpdated;
	UPROPERTY(BlueprintAssignable, Category = "Clue")
		FOnClueAquired OnClueAquired;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		TArray<FItemSetting> InventoryStock;
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		int Clues = 0;
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void BroadcastInventoryEvents();
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		TArray<int> GetInventoryIds();
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool RemoveItemById(int ID);
private:
	//Maybe map a class to an ID?
		//Allowing you to switch the TArray to a TMap of ints n' stuff
	//Need to figure out a way how to get an ID that represents an item. And add a NUMBER to the inventory
	//Need to figure out a way how to get an item from that ID. And give that back.

};
