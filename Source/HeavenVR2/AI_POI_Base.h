// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"

#include "AI_POI_Base.generated.h"
/*

This BP represents a Point of Interest the AI will visit with the appropriate behavior. 
Use this BP to mark specific locations on your level where you want your AI to go

*/

UCLASS()
class HEAVENVR2_API AAI_POI_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAI_POI_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextRenderComponent* TextRender;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* Bounds;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBillboardComponent* Billboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Identifier = FText::FromString("Base");
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector BillboardScale = FVector(5.0f, 5.0f, 5.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector BoundsScale = FVector(5.0f, 5.0f, 5.0f);

};
