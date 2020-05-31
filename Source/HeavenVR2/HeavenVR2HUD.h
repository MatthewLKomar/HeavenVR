// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HeavenVR2HUD.generated.h"

UCLASS()
class AHeavenVR2HUD : public AHUD
{
	GENERATED_BODY()

public:
	AHeavenVR2HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

