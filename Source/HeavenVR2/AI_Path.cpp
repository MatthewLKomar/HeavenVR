// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Path.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AAI_Path::AAI_Path()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Root->SetupAttachment(GetRootComponent());

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetupAttachment(Root);

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(Root);
	Spline->SetClosedLoop(bPathIsLooped, true);
	Spline->SetVisibility(bShowSpline);
	Spline->SetHiddenInGame(bHideSpline);

}

// Called when the game starts or when spawned
void AAI_Path::BeginPlay()
{
	Super::BeginPlay();
	PlaceWayPoints();
	
}

// Called every frame
void AAI_Path::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAI_Path::PlaceWayPoints()
{
	if (bDestroyOldWayPoints == true)
	{
		//Set WayPointTag to group name
		WayPointTag = FName(*WayPointGroupName.ToString());
	}
	else
	{
		SpawnWayPoints();
	}
}

void AAI_Path::DeleteWayPoints()
{
	//Set WayPointTag to group name
	WayPointTag = FName(*WayPointGroupName.ToString());
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), WayPointTag, OutActors);
	for (AActor* Thing : OutActors)
	{
		Thing->Destroy();
	}
}

void AAI_Path::DestroyCurrentWayPoints()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), WayPointTag, OutActors);
	for (AActor* Thing : OutActors)
	{
		Thing->Destroy();
	}
	SpawnWayPoints();
}

void AAI_Path::SpawnWayPoints()
{
	ListOfWayPoints.Empty();
	int PointsOnSpline = Spline->GetNumberOfSplinePoints() - 1;
	for (int i = 0; i <= PointsOnSpline; i++)
	{
		FVector StartLoc = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		FVector UpVector = FVector(0,0,Root->GetComponentRotation().Yaw);
		FVector EndLoc = StartLoc + ((UpVector * -1.0) * TraceDistance);

		FHitResult Result;
		FCollisionQueryParams TraceParams;
		//Do linetrace to detect distance to floor
		GetWorld()->LineTraceSingleByChannel(Result, StartLoc, EndLoc, ECC_Visibility, TraceParams);
		FVector OutLoc = Result.Location;
		OutLoc.Y += FloorOffset;
		FTransform Transform;
		Transform.SetLocation(OutLoc);
		//Spawn AI WayPoint at each spline point's location
		WayPointRef = GetWorld()->SpawnActor<AAI_WayPoint>(WaypointClass, Transform);
		
		//Add new WayPoint to ListOfWayPoints
		ListOfWayPoints.Add(WayPointRef);
		//Clear Tag array
		Tag.Empty();
		//Add WayPoint Name + Index as tag
		Tag.Add(FName(*WayPointGroupName.ToString()));
		//Add the spawned way point reference to an array
		WayPointRef->Tags = Tag;
		//Set WayPoint Group and ID
		WayPointRef->WayPointGroupName = WayPointGroupName;
		WayPointRef->WayPointID = i;
		WayPointRef->SetWayPointInfo();
	}
}

