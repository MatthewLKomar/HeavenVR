// Fill out your copyright notice in the Description page of Project Settings.

#include "FootSteps.h"
#include "GameFramework/Actor.h"
#include "SimplifiedVRChar.h"
#include "Camera/CameraComponent.h"
//#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Math/Vector.h"





// Sets default values for this component's properties
UFootSteps::UFootSteps()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFootSteps::BeginPlay()
{
	Super::BeginPlay();
	Camera = Cast<ASimplifiedVRChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->FindComponentByClass<UCameraComponent>();
	//^^cast to AVrCharacter to get camera location*

}

// Called every frame
void UFootSteps::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bBeginPlay == true && Camera.IsValid()) {
		
		Distance = (Camera->GetComponentLocation() - LastPosition).Size() + Distance;
		LastPosition = Camera->GetComponentLocation();
		if (Distance > StepDistance) {
			Distance = Distance - StepDistance;
			//if (bLastStepRight == true) {
				OnStep.Broadcast(); //broadcasts OnStep event to a blueprint for sound
				bLastStepRight = !bLastStepRight; // next step will be a left step
//
	//		}
		//	else 
			//{
				//OnStep.Broadcast(); //broadcasts OnStep event to a blueprint for sound
				//bLastStepRight = !bLastStepRight;
			//}
		}
	}
	else {
		bBeginPlay = true; // prevents from stepping at begin play
		LastPosition = GetOwner()->GetActorLocation(); //gets your location


	}
}
