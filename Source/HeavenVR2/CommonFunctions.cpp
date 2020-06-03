// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonFunctions.h"
#include "Kismet/KismetSystemLibrary.h"


bool UCommonFunctions::CheckPlayerDist(AActor* Self, AActor* Other, float TraceRadius)
{
	float Distance = Self->GetDistanceTo(Other);
	if (Distance <= TraceRadius)
	{
		return true;
	}
	return false;
}