// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "I_ATS_Fetch.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_ATS_Fetch : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HEAVENVR2_API II_ATS_Fetch
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void GetMesh(USkeletalMeshComponent*& Skelatal, UStaticMeshComponent*&  Static);

};
