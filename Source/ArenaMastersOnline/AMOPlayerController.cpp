// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaMastersOnline.h"
#include "AMOPlayerController.h"

void AAMOPlayerController::InitInputSystem()
{
	//if (PlayerInput == NULL)
	//{
	//	TSubclassOf<UPlayerInput> newPlayerInput = UAMOPlayerInput::StaticClass();
	//	PlayerInput = NewObject<UAMOPlayerInput>(newPlayerInput);
	//}
	Super::InitInputSystem();
}

bool AAMOPlayerController::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	UAMOPlayerInput* Input = Cast<UAMOPlayerInput>(PlayerInput);
	if (Input != NULL)
	{
		Input->ExecuteCustomBind(Key, EventType);
	}
	return Super::InputKey(Key, EventType, AmountDepressed, bGamepad);
}

void AAMOPlayerController::Possess(APawn* inPawn)
{
	Super::Possess(inPawn);
}

void AAMOPlayerController::CastSpell(int32 SpellIndex)
{
	int32 testing = SpellIndex;
}