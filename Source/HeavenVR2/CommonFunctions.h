// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"

#include "CommonFunctions.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENVR2_API UCommonFunctions : public UObject
{
	GENERATED_BODY()

public:
	bool CheckPlayerDist(AActor* Self, AActor* Other, float TraceRadius);
};
