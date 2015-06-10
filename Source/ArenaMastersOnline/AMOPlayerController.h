// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AMOPlayerInput.h"
#include "GameFramework/PlayerController.h"
#include "AMOPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARENAMASTERSONLINE_API AAMOPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual bool InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad) override;

	virtual void InitInputSystem() override;

	virtual void Possess(APawn* inPawn) override;

	void CastSpell(int32 index);
};

