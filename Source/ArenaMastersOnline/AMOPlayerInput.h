// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerInput.h"
#include "AMOPlayerInput.generated.h"

/**
 * 
 */

USTRUCT()
struct FCustomKeyBinding
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		FName KeyName;
	UPROPERTY()
		TEnumAsByte<EInputEvent> EventType;
	UPROPERTY()
		FString Command;
};

UCLASS()
class ARENAMASTERSONLINE_API UAMOPlayerInput : public UPlayerInput
{
public:
	GENERATED_BODY()

	UPROPERTY(Config)
		TArray<FCustomKeyBinding> CustomBinds;

	virtual bool ExecuteCustomBind(FKey Key, EInputEvent EventType);
};
