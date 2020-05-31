// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HeavenVR2GameMode.h"
#include "HeavenVR2HUD.h"
#include "HeavenVR2Character.h"
#include "UObject/ConstructorHelpers.h"

AHeavenVR2GameMode::AHeavenVR2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AHeavenVR2HUD::StaticClass();
}
