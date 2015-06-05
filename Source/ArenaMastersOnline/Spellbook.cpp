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
	
	for (auto cooldownIterator = cooldowns.CreateConstIterator(); cooldownIterator; cooldownIterator++)
	{
		ASpell* tempSpellID = Cast<ASpell*>(cooldownIterator.Value);
	}
}

