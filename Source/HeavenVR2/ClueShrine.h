// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"//Static mesh Component
#include "Components/BoxComponent.h" //Box Collider 
#include "Components/SceneComponent.h"
#include "Engine/DataTable.h"
#include "ItemSettings.h" // So we know what the player has 
#include "Item.h" //Our item that player picks up
#include "ClueShrine.generated.h"

UCLASS()
class HEAVENVR2_API AClueShrine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClueShrine();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UDataTable* ItemDataTable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* Shrine;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent* Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USceneComponent* ClueSpot1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USceneComponent* ClueSpot2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USceneComponent* ClueSpot3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USceneComponent* ClueSpot4;

	/** called when something enters the sphere component */
	UFUNCTION()
		void OnOverlapBegin(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
		TArray<int> FindCluesFromData(UDataTable* Table);
	UFUNCTION(BlueprintCallable)
		TArray<FItemSetting> GetCluesFromPlayer(TArray<FItemSetting> Inventory, UDataTable* Table);
	//UFUNCTION()
		//TArray<AItem*> SpawnCluesToShrine(TArray<FItemSetting> Items, UDataTable* Table);
};
