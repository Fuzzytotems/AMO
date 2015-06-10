// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaMastersOnline.h"
#include "Spell.h"


// Sets default values
ASpell::ASpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InitStats();
}

void ASpell::InitStats()
{
	MinDamage = BaseMinDamage;
	MaxDamage = BaseMaxDamage;
	CooldownElapsed = 0.f;
	Cooldown = BaseCooldown;
	bIsOnCooldown = false;
	CastTime = BaseCastTime;
	ResourceCost = BaseResourceCost;
	AimType = BaseAimType;
	CastingType = BaseCastingType;
	DisableType = BaseDisableType;
	bIsBouncy = bBaseIsBouncy;
	bCastWhileMoving = bBaseCastWhileMoving;
	MagicSchools = BaseMagicSchools;
	MaxCharges = BaseMaxCharges;
	CurrentCharges = MaxCharges;
	SpellLifetime = BaseSpellLifetime;
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