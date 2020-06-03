// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/BillboardComponent.h"

#include "AI_BoundingBox.generated.h"

UCLASS()
class HEAVENVR2_API AAI_BoundingBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAI_BoundingBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* Bounds;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Marker;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextRenderComponent* PathName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBillboardComponent* Billboard;


private:
	FVector TextScale = FVector(1.0, 1.0, 1.0);
	FVector BillboardScale = FVector(5.0, 5.0, 5.0);

public: 

	FVector BoundsScale = FVector(5.0, 5.0, 5.0);
	bool bMarkerVisibleInEditor = true;
	bool bMarkerHiddenInGame = true;

};
