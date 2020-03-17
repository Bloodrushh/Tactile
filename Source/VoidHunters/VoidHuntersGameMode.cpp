// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "VoidHuntersGameMode.h"
#include "VoidHuntersHUD.h"
#include "VoidHuntersCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVoidHuntersGameMode::AVoidHuntersGameMode()
	: Super()
{
	// use our custom HUD class
	HUDClass = AVoidHuntersHUD::StaticClass();
}
