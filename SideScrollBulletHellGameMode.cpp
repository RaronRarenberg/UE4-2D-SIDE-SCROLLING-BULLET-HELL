// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SideScrollBulletHellGameMode.h"
#include "SideScrollBulletHellCharacter.h"

ASideScrollBulletHellGameMode::ASideScrollBulletHellGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ASideScrollBulletHellCharacter::StaticClass();	
}
