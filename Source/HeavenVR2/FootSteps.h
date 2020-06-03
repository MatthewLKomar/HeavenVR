// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"

#include "FootSteps.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStep);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEAVENVR2_API UFootSteps : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFootSteps();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	TWeakObjectPtr<class UCameraComponent> Camera;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector LastPosition = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StepDistance = 100.f;

private: 

	float Distance = 0.f;
	bool bBeginPlay = false;
	bool bLastStepRight = false;

	UPROPERTY(BlueprintAssignable)
		FOnStep OnStep;
};
