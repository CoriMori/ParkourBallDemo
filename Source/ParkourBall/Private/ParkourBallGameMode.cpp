// Copyright Epic Games, Inc. All Rights Reserved.

#include "ParkourBallGameMode.h"
#include "UObject/ConstructorHelpers.h"

AParkourBallGameMode::AParkourBallGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Game/Blueprints/Player/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
