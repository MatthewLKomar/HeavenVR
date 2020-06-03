// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "Engine/UserDefinedStruct.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ItemSettings.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Edible,
	Medicine,
	Misc,
	Weapon,
	Armor,
	Key,
};

USTRUCT(BlueprintType)
struct FItemSetting
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Quantity = 1;
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int ItemID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UTexture2D* Thumbnail;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Value = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsQuestItem = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsWeapon = false;
};


UCLASS()
class HEAVENVR2_API UItemSettings : public UUserDefinedStruct
{
	GENERATED_BODY()
	
};
