// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TextRenderComponent.h"
#include "Components/BillboardComponent.h"
#include "AI_WayPoint.generated.h"

UCLASS()
class HEAVENVR2_API AAI_WayPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_WayPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextRenderComponent* PathName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextRenderComponent* ID;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBillboardComponent* Billboard;
	
	UFUNCTION()
		void SetWayPointInfo();

private:
	
public:	
	FText WayPointGroupName = FText::FromString("WayPoint");
	int WayPointID = 0;

	bool TextVisible = false;

};
