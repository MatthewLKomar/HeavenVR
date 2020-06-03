//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!IMPORTANT READ THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//http://prntscr.com/ry0tvf include this in the blueprint if you want to use your hands
//Set Hand needs to overwritten to look like this: http://prntscr.com/ry0wdp
//To my lovely 112 reader, sometimes it's easier to avoid a headache and just use blueprints.
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!IMPORTANT READ THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma once

#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/TargetPoint.h"
#include "MotionControllerComponent.h"
#include "FootSteps.h"
#include "Grabber.h"
#include "Inventory.h"
#include "Components/WidgetInteractionComponent.h"
#include "SimplifiedVRChar.generated.h"

UCLASS()
class HEAVENVR2_API ASimplifiedVRChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASimplifiedVRChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TWeakObjectPtr<class APlayerController> MyPC;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USceneComponent* VRRoot = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* Camera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMotionControllerComponent* LeftController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMotionControllerComponent* RightController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UGrabber* LeftGrabber;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UGrabber* RightGrabber;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* LeftHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* RightHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UWidgetInteractionComponent* RWidgetInteraction;

	UPROPERTY(BlueprintReadWrite)
		class UInventory* Inventory;

	UPROPERTY(VisibleAnywhere)
		class UFootSteps* FootStep;
	UFUNCTION(BlueprintCallable)
		void MoveForward(float Value);
	UFUNCTION(BlueprintCallable)
		void MoveRight(float Value);

	UFUNCTION(BlueprintCallable)
		void GripLeft();

	UFUNCTION(BlueprintCallable)
		void ReleaseLeft();

	UFUNCTION(BlueprintCallable)
		void GripRight();

	UFUNCTION(BlueprintCallable)
		void ReleaseRight();

	UFUNCTION(BlueprintCallable)
		AActor* Grip(UGrabber* Grabber, USkeletalMeshComponent* Hand);
	UFUNCTION(BlueprintCallable)
		AActor* Release(UGrabber* Grabber, USkeletalMeshComponent* Hand);
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		AActor* HeldObject = nullptr;

	UPROPERTY(BlueprintReadWrite)
		FName SocketName = "GripSocket";
	UPROPERTY(BlueprintReadWrite)
		FName FingerTip = "Pointer";

	UPROPERTY(BlueprintReadWrite)
		bool EnableInventory = false;

	UPROPERTY(BlueprintReadWrite)
		bool LGripPressed = false;
	UPROPERTY(BlueprintReadWrite)
		bool RGripPressed = false;
	UPROPERTY(BlueprintReadWrite)
		bool LTriggerPressed = false;
	UPROPERTY(BlueprintReadWrite)
		bool RTriggerPressed = false;

	UFUNCTION(BlueprintCallable)
		bool IsHeadsetOn();
	UFUNCTION(BlueprintCallable)
		bool IsPalmUp(USkeletalMeshComponent* Hand, bool Debug = false);
	UFUNCTION(BlueprintCallable)
		AActor* SpawnInventory(USkeletalMeshComponent* MeshToAttach, TSubclassOf<AActor> UI, bool Debug = false);
	UPROPERTY(BlueprintReadWrite)
		AActor* ItemInHand;
private:
	void ToNextPoint();
	void ToPreviousPoint();
	void MoveToPoint(AActor* PointOfInterst);
private:
	FVector CameraHeight = FVector(0.f, 0.f, 88.f);
	FVector NewCameraOffset = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere)
		float FadeDuration = 2.f;
	TArray<AActor*> TargetPointsFound;
	UPROPERTY(EditAnywhere)
		int StartLocation = 0;
	UPROPERTY(EditAnywhere)
		int CurrentLocation = 0;
	int MaxLocations = 0;


};
