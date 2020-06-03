// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "GroundAnimalBase.h"
#include "AI_DefentLocation.generated.h"

/**
This is used with the AI's Defend Behavior to mark a location the AI wants to defend.
Good example is defending the animal's Home Base.
 */

UCLASS()
class HEAVENVR2_API AAI_DefentLocation : public ATargetPoint
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_DefentLocation();

	UFUNCTION()
		void CheckActor(AActor* Actor);
	UFUNCTION()
		void CallAnimals();
	/** called when something enters the sphere component */
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextRenderComponent* TextRender;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* Trigger;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		bool bActive = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		FVector TriggerScale = FVector(20.0f, 20.0f, 5.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		TArray<AGroundAnimalBase*> GroundAnimals;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetupBehavior)
		TArray<FName> ActorTags;
	UPROPERTY(BlueprintReadWrite, Category = SetupBehavior)
		AActor* OverlappedActor;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
