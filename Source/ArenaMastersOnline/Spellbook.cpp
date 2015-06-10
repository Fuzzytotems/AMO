// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaMastersOnline.h"
#include "Spellbook.h"

// Sets default values
ASpellbook::ASpellbook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;
}

// Called when the game starts or when spawned
void ASpellbook::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpellbook::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	for (auto cooldownIterator = cooldowns.CreateConstIterator(); cooldownIterator; ++cooldownIterator)
	{
		ASpell* tempSpellID = cooldownIterator.Value();

		tempSpellID->ReduceCD(DeltaTime);
	}

	if (bIsCasting == true)
	{
		CastTimeElapsed += DeltaTime;

		if (CastTimeElapsed >= spells[currentSpell]->CastTime)
		{
			spells[currentSpell]->CastSpell(MouseHitResult, Target);
			bIsCasting = false;
			CastTimeElapsed = 0.f;
		}
	}
}

void ASpellbook::CastSpell(int32 SpellIndex, AActor* newTarget, FHitResult newMouseHitResult)
{
	currentSpell = SpellIndex;
	bool lockedOut = false;

	if (spells.Num() < currentSpell)
	{
		ASpell* tempSpell = spells[currentSpell];
		Target = newTarget;
		MouseHitResult = newMouseHitResult;

		for (int i = 0; i < tempSpell->MagicSchools.Num(), !lockedOut; i++)
		{
			auto result = lockouts.Find(tempSpell->MagicSchools[i]);

			if (result)
			{
				lockedOut = true;
			}
		}

		if (!lockedOut)
		{
			bIsCasting = true;
		}
	}
}