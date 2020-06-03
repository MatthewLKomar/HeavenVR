// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/DataTable.h"

#include "Item.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FItemCreated);

UCLASS()
class HEAVENVR2_API AItem : public AStaticMeshActor
{
	GENERATED_BODY()
		AItem();
public: 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UDataTable* ItemDataTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ItemID;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName ItemName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int Amount = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool IsQuestItem;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool IsWeapon;
	UFUNCTION(BlueprintCallable)
		void PickUp(int &ID, bool &QuestItem, int &AmountOfItems);
	UFUNCTION(BlueprintCallable)
		bool Drop(int Identifier);
	UFUNCTION(BlueprintCallable)
		bool CreateItem();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UStaticMesh* ThisMesh;
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
		FItemCreated ItemCreated;
};
