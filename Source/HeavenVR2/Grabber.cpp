// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Pull-Push Mechanic
	if (GrabbedObject && bIsPullingOrPushing)
	{
		// Update controller location & rotation
		ControllerLocation = GetAttachParent()->GetComponentLocation();
		ControllerRotation = GetAttachParent()->GetComponentRotation();

		UpdatePullPush();
	}
	// Update grabbed object location & rotation (if any)
	else if (GrabbedObject && !bManualAttach) {

		// Update controller location & rotation
		ControllerLocation = GetAttachParent()->GetComponentLocation();
		ControllerRotation = GetAttachParent()->GetComponentRotation();

		switch (GrabType)
		{
		case EGrabTypeEnum::PRECISION_GRAB:
		case EGrabTypeEnum::SNAP_GRAB:

			// Add controller rotation offsets
			ControllerRotation.Add(StandardOffset.Pitch, StandardOffset.Yaw, StandardOffset.Roll);
			if (RotationOffset != FRotator::ZeroRotator)
			{
				ControllerRotation.Add(RotationOffset.Pitch, RotationOffset.Yaw, RotationOffset.Roll);
			}

			// Set grabbed object rotation
			GrabbedObject->SetTargetLocation(ControllerLocation + (ControllerRotation.Vector() * DistanceFromController));
			GrabbedObject->SetTargetRotation(ControllerRotation);
			break;

		case EGrabTypeEnum::LOCK_GRAB:
		case EGrabTypeEnum::DANGLING_GRAB:
		case EGrabTypeEnum::PRECISION_LOCK:
			GrabbedObject->SetTargetLocation(ControllerLocation + (ControllerRotation.Vector() * DistanceFromController));
			break;

		default:
			break;
		}
	}

}


// Ray-Cast and grab an Actor
AActor* UGrabber::Grab(float Reach,
	bool DoRadialTrace, 
	bool ScanOnlyWillManuallyAttach,
	EGrabTypeEnum GrabMode, 
	FName TagName, 
	FRotator Rotation_Offset,
	bool RetainObjectRotation,
	bool RetainDistance,
	bool ShowDebug)
{
	// Set component vars
	GrabType = GrabMode;
	DistanceFromController = Reach;
	RotationOffset = Rotation_Offset;
	bManualAttach = ScanOnlyWillManuallyAttach;

	// Update controller location & rotation
	ControllerLocation = GetAttachParent()->GetComponentLocation();
	ControllerRotation = GetAttachParent()->GetComponentRotation();

	// Calculate Standard Offset - invert Roll to ensure rotation of grabbed objects are retained
	if (ControllerRotation.Roll < 0)
	{
		StandardOffset = FRotator(0.f, 0.f, FMath::Abs(ControllerRotation.Roll));
	}
	else if (ControllerRotation.Roll > 0)
	{
		StandardOffset = FRotator(0.f, 0.f, ControllerRotation.Roll * -1.f);
	}

	// Show Debug line (helpful for a visual indicator during testing)
	if (ShowDebug) {

		if (DoRadialTrace)
		{
			// Draw Debug Sphere
			DrawDebugSphere(
				GetWorld(),
				this->GetComponentLocation(),
				Reach / 2, 8,
				FColor(255, 0, 0),
				false, 1.f, 0,
				1.f
			);
		}
		else
		{
			// Draw Debug Line Trace
			DrawDebugLine(
				GetWorld(),
				this->GetComponentLocation(),
				this->GetComponentLocation() + (this->GetComponentRotation().Vector() * Reach),
				FColor(255, 0, 0),
				false, -1.f, 0,
				12.f
			);
		}
	}

	// Calculate Reach
	Reach = DoRadialTrace ? Reach / 2 : Reach;

	// Line trace
	AActor* ActorHit = GetHit(DoRadialTrace, Reach, this->GetComponentLocation(), this->GetComponentLocation() + (this->GetComponentRotation().Vector() * Reach), RetainDistance, ShowDebug);

	// Check if there's a valid object to grab
	if (ActorHit)
	{
		// Only grab an object with a Physics Handle
		GrabbedObject = ActorHit->FindComponentByClass<UPhysicsHandleComponent>();
		//UE_LOG(LogTemp, Warning, TEXT("GRABBER - I grabbed : %s"), *ActorHit->GetName());

		// Automatic Attachment - Attach to Physics Handle
		if (GrabbedObject)
		{
			// Check for actor tag
			if (!TagName.IsNone())
			{
				if (!GrabbedObject->ComponentHasTag(TagName))
				{
					//UE_LOG(LogTemp, Warning, TEXT("GRABBER - Couldn't find %s tag in this physics handle."), *TagName.ToString());
					return nullptr;
				}
			}

			// Do a Physics Handle Grab if automatic attachment is selected
			if (!bManualAttach)
			{
				// Physics Handle found! Attempt to Grab Object
				UPrimitiveComponent* ComponentToGrab = Cast<UPrimitiveComponent>(ActorHit->GetRootComponent());

				// Make object face controller
				//FRotator TempRotator = UKismetMathLibrary::FindLookAtRotation(GrabbedObject->GetOwner()->GetActorLocation(), GetAttachParent()->GetComponentLocation());
				//GrabbedObject->SetTargetRotation(TempRotator);

				// Check for precision grab 
				//CONVERTED INTO A SWITCH STATMENT FROM A BUNCH OF IF STATMENTSs 
				switch (GrabType)
				{
				case EGrabTypeEnum::PRECISION_GRAB:
					// Grab
					GrabbedObject->GrabComponentAtLocationWithRotation(
						ComponentToGrab,
						NAME_None,
						NewGrabbedLocation, // NewGrabbedLocation holds the impact point of the line trace
						RetainObjectRotation ? ActorHit->GetActorRotation() : ControllerRotation
					);

					// Set transform
					GrabbedObject->SetTargetLocation(ControllerLocation + (ControllerRotation.Vector() * DistanceFromController));
					GrabbedObject->SetTargetRotation(ControllerRotation);
					break;
				case EGrabTypeEnum::DANGLING_GRAB:
					// Grab
					GrabbedObject->GrabComponentAtLocation(
						ComponentToGrab,
						NAME_None,
						NewGrabbedLocation // NewGrabbedLocation holds the impact point of the line trace
					);

					// Set transform
					GrabbedObject->SetTargetLocation(ControllerLocation + (ControllerRotation.Vector() * DistanceFromController));
					GrabbedObject->SetTargetRotation(ControllerRotation);
					break;
				case EGrabTypeEnum::PRECISION_LOCK:// Grab
					GrabbedObject->GrabComponentAtLocationWithRotation(
						ComponentToGrab,
						NAME_None,
						NewGrabbedLocation, // NewGrabbedLocation holds the impact point of the line trace
						RetainObjectRotation ? ActorHit->GetActorRotation() : ControllerRotation
					);

					// Set transform
					GrabbedObject->SetTargetLocation(ControllerLocation + (ControllerRotation.Vector() * DistanceFromController));
					break;
				default:
					// Grab
					GrabbedObject->GrabComponentAtLocationWithRotation(
						ComponentToGrab,
						NAME_None,
						ActorHit->GetActorLocation(),
						RetainObjectRotation ? ActorHit->GetActorRotation() : FRotator::ZeroRotator
					);

					// Set transform
					GrabbedObject->SetTargetLocation(ControllerLocation + (ControllerRotation.Vector() * DistanceFromController));
					if (GrabType == EGrabTypeEnum::SNAP_GRAB)
					{
						GrabbedObject->SetTargetRotation(ControllerRotation);
					}
					break;
				}
			}
			if (ShowDebug)
			{
				UE_LOG(LogTemp, Warning, TEXT("GRABBER - Returning Actor %s."), *ActorHit->GetName());
			}
			return ActorHit;
		}

	}

	return nullptr;
}

// Raycast and get any object hit by the line trace
AActor* UGrabber::GetHit(bool DoRadialTrace, float Reach, FVector LineTraceStart, FVector LineTraceEnd, bool RetainDistance, bool bShowDebugLine)
{

	// Set a default grabbable object type if none was specified
	if (Grabbable_ObjectTypes.Num() < 1)
	{
		Grabbable_ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
	}

	// Check if we need to do a radial trace or a simple line trace
	FHitResult	Hit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	if (DoRadialTrace)
	{
		// Do a radial trace
		TArray <struct FHitResult> HitResults;
		FCollisionShape CollisionShape;
		CollisionShape.ShapeType = ECollisionShape::Sphere;
		CollisionShape.SetSphere(Reach);
		GetWorld()->SweepMultiByObjectType
		(
			HitResults,
			LineTraceStart,
			LineTraceStart,
			FQuat(0.f, 0.f, 0.f, 0.f),
			FCollisionObjectQueryParams(Grabbable_ObjectTypes),
			CollisionShape,
			TraceParameters
		);

		// Return the first hit result
		if (HitResults.Num() > 0)
		{
			Hit = HitResults[0];
		}
	}
	else
	{
		// Do line trace / ray-cast
		GetWorld()->LineTraceSingleByObjectType(
			Hit,
			LineTraceStart,
			LineTraceEnd,
			FCollisionObjectQueryParams(Grabbable_ObjectTypes),
			TraceParameters
		);
	}


	// See what we hit
	auto ActorHit = Hit.GetActor();

	// Return any hits
	if (ActorHit) {

		// Update Distance with hit distance
		if (!RetainDistance)
		{
			DistanceFromController = Hit.Distance;
		}

		// Set Grabbed transform for precision grabs
		NewGrabbedLocation = Hit.ImpactPoint;

		// Send back actor that was hit by the line trace
		return ActorHit;
	}
	else {
		return nullptr;
	}
}

// Release hold of object
AActor* UGrabber::Release()
{
	if (GrabbedObject) {


		// Check if we're currently pulling or pushing the grabbed object
		if (bIsPullingOrPushing)
		{
			StopPull();
			StopPush();
		}

		// Save the currently attached object
		AActor* CurrentlyGrabbed = GrabbedObject->GetOwner();

		if (!bManualAttach)
		{
			// Player has latched on to something, release it
			GrabbedObject->ReleaseComponent();
		}

		GrabbedObject = nullptr;
		return CurrentlyGrabbed;
	}

	return nullptr;
}
// Set distance from controller
void UGrabber::SetDistanceFromController(float NewDistance, float MinDistance, float MaxDistance)
{
	// Set specified bounds
	MinDistanceFromController = MinDistance;
	MaxDistanceFromController = MaxDistance;

	//UE_LOG(LogTemp, Warning, TEXT("GRABBER - MinDistance: %f   MaxDistance: %f"), MinDistanceFromController, MaxDistanceFromController);
	//UE_LOG(LogTemp, Warning, TEXT("GRABBER - CurrentDistance: %f   Speed: %f"), DistanceFromController, Speed);

	// Check if we're pulling
	if (Speed < 0.f)
	{
		if (NewDistance > MinDistanceFromController) {
			DistanceFromController = NewDistance;
			if (GrabbedObject)
			{
				// Update controller location & rotation
				//UE_LOG(LogTemp, Warning, TEXT("GRABBER - PULLING..."));
				ControllerLocation = GetAttachParent()->GetComponentLocation();
				ControllerRotation = GetAttachParent()->GetComponentRotation();
				GrabbedObject->SetTargetLocation(ControllerLocation + (ControllerRotation.Vector() * DistanceFromController));

			}
		}
	}
	// Check if we're pushing
	else if (Speed > 0.f)
	{
		if (NewDistance < MaxDistanceFromController) {
			DistanceFromController = NewDistance;
			if (GrabbedObject)
			{
				// Update controller location & rotation
				//UE_LOG(LogTemp, Warning, TEXT("GRABBER - PUSHING..."));
				ControllerLocation = GetAttachParent()->GetComponentLocation();
				ControllerRotation = GetAttachParent()->GetComponentRotation();
				GrabbedObject->SetTargetLocation(ControllerLocation + (ControllerRotation.Vector() * DistanceFromController));
			}
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("GRABBER - NewDistance: %f   Speed: %f"),NewDistance, Speed);

}

// Pull grabbed object
void UGrabber::PullGrabbedObject(float PullSpeed, float MinDistance, float MaxDistance)
{
	// Update controller location & rotation
	ControllerLocation = GetAttachParent()->GetComponentLocation();
	ControllerRotation = GetAttachParent()->GetComponentRotation();

	if (GrabbedObject) {
		// Set variables and begin pull
		Speed = FMath::Abs(PullSpeed) * -1.f;
		MinDistanceFromController = MinDistance;
		MaxDistanceFromController = MaxDistance;
		bIsPullingOrPushing = true;
	}
}

// Push grabbed object
void UGrabber::PushGrabbedObject(float PushSpeed, float MinDistance, float MaxDistance)
{
	// Update controller location & rotation
	ControllerLocation = GetAttachParent()->GetComponentLocation();
	ControllerRotation = GetAttachParent()->GetComponentRotation();

	if (GrabbedObject) {
		// Set variables and begin pull
		Speed = FMath::Abs(PushSpeed);
		MinDistanceFromController = MinDistance;
		MaxDistanceFromController = MaxDistance;
		bIsPullingOrPushing = true;
	}
}

// Update Pulled-Pushed Object
void UGrabber::UpdatePullPush()
{
	// Get the distance from the controller
	DistanceFromController = FVector::Distance(ControllerLocation, GrabbedObject->GetOwner()->GetActorLocation());

	// Try to set the new distance
	SetDistanceFromController(DistanceFromController + Speed, MinDistanceFromController, MaxDistanceFromController);
}

// Stop Pull
AActor* UGrabber::StopPull()
{
	if (Speed < 0.f)
	{
		// Stop Pull
		bIsPullingOrPushing = false;
	}
	else
	{
		return nullptr;
	}

	if (GrabbedObject)
	{
		// Save the currently attached object
		AActor* CurrentlyGrabbed = GrabbedObject->GetOwner();
		return CurrentlyGrabbed;
	}

	return nullptr;
}


// Stop ush
AActor* UGrabber::StopPush()
{
	if (Speed > 0.f)
	{
		// Stop Push
		bIsPullingOrPushing = false;
	}
	else
	{
		return nullptr;
	}

	if (GrabbedObject)
	{
		// Save the currently attached object
		AActor* CurrentlyGrabbed = GrabbedObject->GetOwner();
		return CurrentlyGrabbed;
	}

	return nullptr;
}
