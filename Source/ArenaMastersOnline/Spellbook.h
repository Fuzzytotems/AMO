// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ContainersFwd.h"
#include "Spell.h"
#include "GameFramework/Actor.h"
#include "Spellbook.generated.h"

UCLASS()
class ARENAMASTERSONLINE_API ASpellbook : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpellbook();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	TMap<int32, ASpell*> cooldowns;

	UPROPERTY(BlueprintReadOnly, Category = Spells)
		TArray<int32> spells;

private:
	int32 currentSpell;
	int32 previousSpell;
};
