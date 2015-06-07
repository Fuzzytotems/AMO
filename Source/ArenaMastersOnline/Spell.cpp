// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaMastersOnline.h"
#include "Spell.h"


// Sets default values
ASpell::ASpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseCooldown = 0;
	Cooldown = 0;
	CooldownElapsed = 0;

	bIsOnCooldown = false;

	InitStats();
}

void ASpell::InitStats()
{

}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpell::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool ASpell::ReduceCD(float DeltaTime)
{
	CooldownElapsed -= DeltaTime;

	FMath::Clamp(CooldownElapsed, 0.f, Cooldown);

	if (CooldownElapsed == 0.f)
	{
		bIsOnCooldown = false;

		if (CurrentCharges < MaxCharges)
		{
			CurrentCharges++;
		}

		return true;
	}

	return false;
}