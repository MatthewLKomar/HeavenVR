// Fill out your copyright notice in the Description page of Project Settings.
#include "VrCharacter.h"
#include "Engine/World.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "IHeadMountedDisplay.h"
#include "XRMotionControllerBase.h"
#include "Components/SceneComponent.h"

// Sets default values. This is a constructor.
AVrCharacter::AVrCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot")); //Creating VrOrigin Scene Component
	VRRoot->SetupAttachment(GetRootComponent()); //Attaching VrOrigin to root component (this case a capsule component)
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); //Creating the camera
	Camera->SetupAttachment(VRRoot); //attaches camera to Vr Origin

	FootStep = CreateDefaultSubobject<UFootSteps>(TEXT("Foot Steps Component")); //Attaches the footstep to the VrCharacter

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory Component")); //Attaches the inventory to the VrCharacter

	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Controller"));
	LeftController->SetupAttachment(VRRoot);
	LeftController->SetTrackingMotionSource(FXRMotionControllerBase::LeftHandSourceId);
	LeftController->SetRelativeLocation(FVector(0.f, 0.f, 110.f));

	LeftGrabber = CreateDefaultSubobject<UGrabber>(TEXT("Left Grabber"));
	LeftGrabber->SetupAttachment(LeftController);

	LeftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"));
	LeftHand->SetupAttachment(LeftController);

	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Controller"));
	RightController->SetupAttachment(VRRoot);
	RightController->SetTrackingMotionSource(FXRMotionControllerBase::RightHandSourceId);
	RightController->SetRelativeLocation(FVector(0.f, 0.f, 110.f));

	RightGrabber = CreateDefaultSubobject<UGrabber>(TEXT("Right Grabber"));
	RightGrabber->SetupAttachment(RightController);

	RightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	RightHand->SetupAttachment(RightController);

	//Handles UI interaction
	RWidgetInteraction = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Right Widget Interaction Component"));
	RWidgetInteraction->SetupAttachment(RightHand);

}

// Called when the game starts or when spawned
void AVrCharacter::BeginPlay()
{	Super::BeginPlay();
	//We're Attaching our widget interaction components in begin play because
	//ue4 doesn't let us do it in the constructor
	RWidgetInteraction->AttachToComponent(RightHand, 
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget,true), FingerTip);
	// Set tracking origin (Oculus & Vive)
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
}

// Called every frame
void AVrCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Calculations to deal with collison. This basically prevents us from walking through walls
	NewCameraOffset = Camera->GetComponentLocation() - GetActorLocation();
	NewCameraOffset.Z = 0;
	AddActorWorldOffset(NewCameraOffset);
	
	VRRoot->AddWorldOffset(-NewCameraOffset);
	EnableInventory = IsPalmUp(LeftHand);
	/*
	Blueprint equivalent of this code would go after this  all
	if (EnableInventory == true && LGripPressed == false && LTriggerPressed == false )
	{
		
	}*/
}

// Called to bind functionality to input
void AVrCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AVrCharacter::MoveForward);
	//PlayerInputComponent->BindAxis(TEXT("Right"), this, &AVrCharacter::MoveRight);
	
	PlayerInputComponent->BindAction("GripLeft",IE_Pressed, this, &AVrCharacter::GripLeft);
	PlayerInputComponent->BindAction("GripLeft", IE_Released, this, &AVrCharacter::ReleaseRight);


	PlayerInputComponent->BindAction(TEXT("GripRight"), IE_Pressed, this, &AVrCharacter::GripRight);
	PlayerInputComponent->BindAction(TEXT("GripRight"), IE_Released, this, &AVrCharacter::ReleaseRight);


}

void AVrCharacter::MoveForward(float throttle) {
	AddMovementInput(throttle * Camera->GetForwardVector());
}

void AVrCharacter::MoveRight(float throttle){
	AddMovementInput(throttle * Camera->GetRightVector());

}

void AVrCharacter::GripLeft()
{
	HeldObject = Grip(LeftGrabber, LeftHand);
	ItemInHand = HeldObject;
}

void AVrCharacter::ReleaseLeft()
{
	HeldObject = Release(LeftGrabber, LeftHand);
	ItemInHand = HeldObject;
}

void AVrCharacter::GripRight()
{
	HeldObject = Grip(RightGrabber, RightHand);
	ItemInHand = HeldObject;
}

void AVrCharacter::ReleaseRight()
{
	HeldObject = Release(RightGrabber, RightHand);
	ItemInHand = HeldObject;
}


AActor* AVrCharacter::Grip(UGrabber* Grabber, USkeletalMeshComponent* Hand)
{
	auto Held = Grabber->Grab(20.0f, true, true, EGrabTypeEnum::PRECISION_GRAB, "");
	if (Held)
	{
		FAttachmentTransformRules TransformRules = FAttachmentTransformRules(
			EAttachmentRule::SnapToTarget,
			true);
		Held->AttachToComponent(Hand, TransformRules,SocketName);
		return Held;
	}
	return nullptr;
}

AActor* AVrCharacter::Release(UGrabber* Grabber, USkeletalMeshComponent* Hand)
{
	auto Held = Grabber->Release();
	if (Held)
	{
		FDetachmentTransformRules TransformRules = FDetachmentTransformRules(
			EDetachmentRule::KeepWorld,
			true);
		Held->DetachFromActor(TransformRules);
		return Held;
	}
	return nullptr;
}

bool AVrCharacter::IsPalmUp(USkeletalMeshComponent* Hand, bool Debug)
{
	if ((Hand->GetSocketRotation("").Roll <= -120.0f && Hand->GetSocketRotation("").Roll >= -180.0f) ||
		(Hand->GetSocketRotation("").Roll <= 180.0f && Hand->GetSocketRotation("").Roll >= 155.0f))
	{
		if (Debug)
		{
			UE_LOG(LogTemp, Error, TEXT("Can Inventory, %f"), Hand->GetSocketRotation("").Roll);
		}
		return true;
	}
	if (Debug)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't Inventory, %f"), Hand->GetSocketRotation("").Roll);
	}
	return false;
	
}

AActor* AVrCharacter::SpawnInventory(USkeletalMeshComponent* MeshToAttach, TSubclassOf<AActor> UI, bool Debug)
{
	FVector location = GetActorLocation();
	FRotator rotation = GetActorRotation();
	auto UIObject = GetWorld()->SpawnActor(UI, &location, &rotation);
	if (UIObject != nullptr)
	{
		FAttachmentTransformRules TransformRules = FAttachmentTransformRules(
			EAttachmentRule::SnapToTarget,
			true);
		UIObject->AttachToComponent(MeshToAttach, TransformRules, SocketName);
		return UIObject;
	}
	return nullptr;
}

// Check if the HMD is worn
bool AVrCharacter::IsHeadsetOn()
{
	if (UHeadMountedDisplayFunctionLibrary::GetHMDWornState() == EHMDWornState::Worn)
	{
		return true;
	}

	return false;
}

