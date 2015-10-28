// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaMastersOnline.h"
#include "AINPCController.h"

AAINPCController::AAINPCController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bWantsPlayerState = true;
}