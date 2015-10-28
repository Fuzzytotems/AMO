// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include <fstream>
#include "ArenaPlayerState.h"
#include "GameFramework/GameMode.h"
#include "ArenaMastersOnlineGameMode.generated.h"

UCLASS(minimalapi)
class AArenaMastersOnlineGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AArenaMastersOnlineGameMode(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = BotInfo)
		TSubclassOf<AArenaPlayerState> BotState;
};