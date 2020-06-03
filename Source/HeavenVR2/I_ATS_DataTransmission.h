// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_ATS_DataTransmission.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_ATS_DataTransmission : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HEAVENVR2_API II_ATS_DataTransmission
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void TransmissionSlotName(const FString& SlotName);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SetTransmissionStatus(bool bEndOfDataTransmission);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		bool GetTransmissionStatus(); //bDataReceived
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		FString GetSlotName();

};
