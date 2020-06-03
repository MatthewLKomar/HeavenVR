// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
//#include "Components/WidgetComponent.h"
#include "Animation/AnimMontage.h"
#include "Components/SphereComponent.h"
#include "Engine/EngineTypes.h"

#include "I_GroundAnimals.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_GroundAnimals : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HEAVENVR2_API II_GroundAnimals
{
	GENERATED_BODY()
// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent) //not needed cuz not using widget display
		//void GetWidgets(UWidgetComponent*& WBPTame, UWidgetComponent*& WBPHud, UWidgetComponent*& WBPPet);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void GetSpeedAndAcceleration(float& MaxSpeed, float& MaxAcceleration);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void GetAnimalHP(float& HP);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SetAnimalCurrentHP(float HP);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionBecomePet();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void DisableDayCycle();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionLeave();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void ShowPetMarker();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void NotifyNameChange();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		FText GetAnimalName();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		FText GetCompanionName();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SetCompanionName(const FText& CompanionName);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void LeaveGroup();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionFollowStart();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionFollowEnd();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionStayStart();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionStayEnd();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionGoLocStart();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionGoLocEnd();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionAttackStart();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionAttackEnd();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		float GetMovementAcceptanceRadius();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		float GetDisengageCD();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SetStateAttacking(bool Attacking);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		float GetAttackFrequency();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void FinishedEating();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void DisengageAnimal();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void PlayAttackAnimation();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		UAnimMontage* GetCurrentMontage();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		USphereComponent* GetCollisionAttackVolume();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		EObjectTypeQuery GetDamageObjectTypes();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void ApplyMeleeDamage();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void EnableDayCycle();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void HideWidgetMarker();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void ShowWidgetMarker();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void PauseComponents();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void UnpauseComponents();

};
