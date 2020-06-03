// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Animal_Enums.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "I_ATS_PlayerConn.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_ATS_PlayerConn : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HEAVENVR2_API II_ATS_PlayerConn
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void AddBait(int BaitAmount, EBaitType BaitType);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void GetSpawnAnchor(UStaticMeshComponent* Anchor, UCameraComponent* Camera);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		bool GetAnimMode();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		bool GetIsFalling();
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//	void SetCompanionName_ATS(const FText& CompanionName);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SetCompanionName(const FText& NewName);
};
