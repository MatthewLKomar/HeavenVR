// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/BillboardComponent.h"
#include "AI_WayPoint.h"

#include "AI_Path.generated.h"

UCLASS()
class HEAVENVR2_API AAI_Path : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAI_Path();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USplineComponent* Spline;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBillboardComponent* Billboard;

	UFUNCTION()
		void PlaceWayPoints();
	UFUNCTION()
		void DeleteWayPoints();
	UFUNCTION()
		void DestroyCurrentWayPoints();
	UFUNCTION()	
		void SpawnWayPoints();

private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName WayPointTag = TEXT("Path1");
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentInt = 0;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AAI_WayPoint* WayPointRef;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AAI_WayPoint> WaypointClass;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> Tag;

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText WayPointGroupName = FText::FromString("Path1");
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TraceDistance = 3000.0;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bPathIsLooped = false;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FloorOffset = 50.0;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bDestroyOldWayPoints = false;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AAI_WayPoint*> ListOfWayPoints;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bGoingForward = true;//Go through the path forward?
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bShowSpline = true;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bHideSpline = true;


};
