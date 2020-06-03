// Fill out your copyright notice in the Description page of Project Settings.

/*
All of the Grabber logic here was originally written by: 
https://github.com/1runeberg/RunebergVRPlugin/blob/master/Plugins/RunebergVRPlugin/RunebergVRPlugin.uplugin
However, I slightly modified it. 
*/
#pragma once

#include "Engine.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UENUM(BlueprintType)
enum class EGrabTypeEnum : uint8
{
	PRECISION_GRAB 	UMETA(DisplayName = "Precision Grab"),
	SNAP_GRAB 		UMETA(DisplayName = "Snap to Mesh Origin Grab"),
	LOCK_GRAB		UMETA(DisplayName = "Locked Rotation Grab"),
	DANGLING_GRAB	UMETA(DisplayName = "Precision Grab and Dangle"),
	PRECISION_LOCK	UMETA(DisplayName = "Precision Grab with Locked Rotation")

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEAVENVR2_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** These are the objects that can be grabbed, needs a physics handle component if you want object to auto attach */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		TArray<TEnumAsByte<EObjectTypeQuery>> Grabbable_ObjectTypes;

	// Current Distance of grabbed items from their respective controllers
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
		float DistanceFromController = 10.0f;

	/** Min Distance for Controller for grabbed objects  - Customize Push & Pull functions mid action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		float MinDistanceFromController = 1.0f;

	/** Min & Max Distance for Controller for grabbed objects  - Customize Push & Pull functions mid action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
		float MaxDistanceFromController = 20.0f;

	// Grab something within line trace range of controller
	UFUNCTION(BlueprintCallable, Category = "VR")
		AActor* Grab(float Reach = 5.f,
			bool DoRadialTrace = false,
			bool ScanOnlyWillManuallyAttach = false,
			EGrabTypeEnum GrabMode = EGrabTypeEnum::PRECISION_GRAB,
			FName TagName = FName(TEXT("")),
			FRotator Rotation_Offset = FRotator::ZeroRotator,
			bool RetainObjectRotation = true,
			bool RetainDistance = false,
			bool ShowDebug = false);

	// Set distance from controller
	UFUNCTION(BlueprintCallable, Category = "VR")
		void SetDistanceFromController(float NewDistance, float MinDistance, float MaxDistance);

	// Release grabbed object
	UFUNCTION(BlueprintCallable, Category = "VR")
		AActor* Release();

	// Pull grabbed object 
	UFUNCTION(BlueprintCallable, Category = "VR")
		void PullGrabbedObject(float PullSpeed = 1.f, float MinDistance = 1.f, float MaxDistance = 20.f);

	// Push grabbed object(s) 
	UFUNCTION(BlueprintCallable, Category = "VR")
		void PushGrabbedObject(float PushSpeed = 1.f, float MinDistance = 1.f, float MaxDistance = 20.f);

	// Stop Pull
	UFUNCTION(BlueprintCallable, Category = "VR")
		AActor* StopPull();

	// Stop Push
	UFUNCTION(BlueprintCallable, Category = "VR")
		AActor* StopPush();

private:
	// Motion Controller Transform
	FVector ControllerLocation = FVector::ZeroVector;
	FRotator ControllerRotation = FRotator::ZeroRotator;

	// Temp Variables
	UPhysicsHandleComponent* GrabbedObject = nullptr;
	EGrabTypeEnum GrabType = EGrabTypeEnum::PRECISION_GRAB;
	FVector NewGrabbedLocation = FVector::ZeroVector;
	FRotator StandardOffset = FRotator::ZeroRotator;
	FRotator RotationOffset = FRotator::ZeroRotator;

	// Get Actor hit by line trace
	AActor* GetHit(bool DoRadialTrace,
		float Reach,
		FVector LineTraceStart,
		FVector LineTraceEnd,
		bool RetainDistance,
		bool bShowDebugLine);
	bool bManualAttach = false;

	// Pull-Push Mechanic
	bool bIsPullingOrPushing = false;
	float Speed = 1.f;
	// Update Pulled-Pushed Object
	void UpdatePullPush();
		
};
