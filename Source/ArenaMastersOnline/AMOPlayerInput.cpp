// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaMastersOnline.h"
#include "AMOPlayerInput.h"

bool UAMOPlayerInput::ExecuteCustomBind(FKey Key, EInputEvent EventType)
{
	for (int32 i = 0; i < CustomBinds.Num(); i++)
	{
		if (FKey(CustomBinds[i].KeyName) == Key && CustomBinds[i].EventType == EventType)
		{
			FStringOutputDevice DummyOut;
			//if (Cast<APlayerController>(GetOuterAPlayerController())->Player->Exec(GetWorld(), *CustomBinds[i].Command, DummyOut))
			
			if (Exec(GetWorld(), *CustomBinds[i].Command, DummyOut))
			{
				return true;
			}
		}
	}

	return false;
}