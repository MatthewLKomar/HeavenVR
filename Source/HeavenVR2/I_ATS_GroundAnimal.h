// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Animation/AnimMontage.h"
#include "Components/SphereComponent.h"
#include "Engine/EngineTypes.h"
#include "I_ATS_GroundAnimal.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_ATS_GroundAnimal : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HEAVENVR2_API II_ATS_GroundAnimal
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent) //not needed cuz not using widget display
	//void GetWidgets(UWidgetComponent*& WBPTame, UWidgetComponent*& WBPHud, UWidgetComponent*& WBPPet);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void GetSpeedAndAcceleration_ATS(float& MaxSpeed, float& MaxAcceleration);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void GetAnimalHP_ATS(float& HP);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SetAnimalCurrentHP_ATS(float HP);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionBecomePet_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void DisableDayCycle_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionLeave_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void ShowPetMarker_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void NotifyNameChange_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		FText GetAnimalName_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		FText GetCompanionName_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SetCompanionName_ATS(const FText& CompanionName);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void LeaveGroup_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionFollowStart_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionFollowEnd_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionStayStart_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionStayEnd_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionGoLocStart_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionGoLocEnd_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionAttackStart_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CompanionAttackEnd_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		float GetMovementAcceptanceRadius_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		float GetDisengageCD_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SetStateAttacking_ATS(bool Attacking);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		float GetAttackFrequency_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void FinishedEating_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void DisengageAnimal_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void PlayAttackAnimation_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		UAnimMontage* GetCurrentMontage_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		USphereComponent* GetCollisionAttackVolume_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		EObjectTypeQuery GetDamageObjectTypes_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void ApplyMeleeDamage_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void EnableDayCycle_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void HideWidgetMarker_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void ShowWidgetMarker_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void PauseComponents_ATS();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void UnpauseComponents_ATS();

};
