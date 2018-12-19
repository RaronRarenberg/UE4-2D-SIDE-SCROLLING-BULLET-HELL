// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SideScrollStaticss.h"
#include "SideScrollBulletHell.h"
#include "SideScrollBulletHellGameMode.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"



/** Find the smallest angle between two headings (in degrees) */
float USideScrollStaticss::FindDeltaAngleDegrees(float A1, float A2)
{
	// Find the difference
	float Delta = A2 - A1;

	// If change is larger than 180
	if (Delta > 180.0f)
	{
		// Flip to negative equivalent
		Delta = Delta - (360.0f);
	}
	else if (Delta < -180.0f)
	{
		// Otherwise, if change is smaller than -180
		// Flip to positive equivalent
		Delta = Delta + (360.0f);
	}

	// Return delta in [-180,180] range
	return Delta;
}

bool USideScrollStaticss::FindLookAtAngle2D(const FVector2D& Start, const FVector2D& Target, float &Angle)
{
	FVector2D Normal = (Target - Start).GetSafeNormal();
	if (!Normal.IsNearlyZero())
	{
		Angle = FMath::RadiansToDegrees(FMath::Atan2(Normal.Y, Normal.X));
		return true;
	}
	return false;
}

ASideScrollBulletHellGameMode* USideScrollStaticss::GetSideScrollBulletHellGameMode(UObject* WorldContextObject)
{
	return Cast<ASideScrollBulletHellGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
}

void USideScrollStaticss::PutInZPlane(AActor* ActorToMove)
{
	if (ASideScrollBulletHellGameMode* GM = USideScrollStaticss::GetSideScrollBulletHellGameMode(ActorToMove))
	{
		FVector Loc = ActorToMove->GetActorLocation();
		Loc.Z = GM->PlayInZPlane;
		ActorToMove->SetActorLocation(Loc);
	}
}

void USideScrollStaticss::PlayFlipbook(UPaperFlipbookComponent* Component, UPaperFlipbook* NewFlipbook, bool bLooping, float PlayRate /*= 1.0f*/, bool bPlayFromStart /*= false*/)
{
	Component->SetFlipbook(NewFlipbook);
	Component->SetLooping(bLooping);
	Component->SetPlayRate(PlayRate);
	if (bPlayFromStart)
	{
		Component->PlayFromStart();
	}
	else
	{
		Component->Play();
	}
}
