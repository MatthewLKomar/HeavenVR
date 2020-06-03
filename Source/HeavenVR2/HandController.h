// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"

#include "HandController.generated.h"

UCLASS()
class HEAVENVR2_API AHandController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandController();

	void SetHand(EControllerHand Hand);
	void PairController(AHandController* Controller);
	
	void Grip();
	void Release();

	// state
	bool bCanClimb = false;
	bool bIsClimbing = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TWeakObjectPtr<class APlayerController> MyPC;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Default sub object 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UMotionControllerComponent* MotionController; //there was a class here


private: 
	//call backs
	UFUNCTION()
	void  ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void  ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);


	FVector ClimbingStartLocation; 
	AHandController* OtherController;



	//helpers
	bool CanClimb() const;
	
	UPROPERTY(EditDefaultsOnly)
		class UHapticFeedbackEffect_Base* HapticEffect;
};
