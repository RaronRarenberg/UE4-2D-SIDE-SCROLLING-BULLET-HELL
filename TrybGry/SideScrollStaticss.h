// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SideScrollStaticss.generated.h"

/**
 *
 */
UCLASS()
class SIDESCROLLBULLETHELL_API USideScrollStaticss : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Calculate angle difference in the range [-180, 180]. */
	UFUNCTION(BlueprintCallable, Category = "Math")
		static float FindDeltaAngleDegrees(float A1, float A2);

	/** Finds the angle between two 2D points. */
	UFUNCTION(BlueprintPure, Category = "Math|Rotator", meta = (Keywords = "rotation rotate"))
		static bool FindLookAtAngle2D(const FVector2D& Start, const FVector2D& Target, float& Angle);

	/** Get the current game mode, pre-cast to ATanksGameMode for convenience. */
	UFUNCTION(BlueprintCallable, Category = "Game")
		static class ASideScrollBulletHellGameMode* GetSideScrollBulletHellGameMode(UObject* WorldContextObject);

	/** Snap this actor to the Z plane that we're using for this level. */
	UFUNCTION(BlueprintCallable, Category = "Game")
		static void PutInZPlane(AActor* ActorToMove);

	/** All-in-one convenience function to play a flipbook. */
	UFUNCTION(BlueprintCallable, Category = "Animation")
		static void PlayFlipbook(class UPaperFlipbookComponent* Component, class UPaperFlipbook* NewFlipbook, bool bLooping, float PlayRate = 1.0f, bool bPlayFromStart = false);
};
