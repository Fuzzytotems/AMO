// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "UnrealNetwork.h"
#include "GameFramework/PlayerState.h"
#include "ArenaPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ARENAMASTERSONLINE_API AArenaPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	// CD Management
	UFUNCTION(BlueprintCallable, Category = Cooldowns)
		void AddCooldown(FName spellName, float duration);
	void AddCooldownImplementation(FName spellName, float duration);
	UFUNCTION(reliable, Client, WithValidation)
		void ClientAddCooldown(FName spellName, float duration);
	UFUNCTION(reliable, server, WithValidation)
		void ServerAddCooldown(FName spellName, float duration);
	virtual bool ClientAddCooldown_Validate(FName spellName, float duration);
	virtual void ClientAddCooldown_Implementation(FName spellName, float duration);
	virtual bool ServerAddCooldown_Validate(FName spellName, float duration);
	virtual void ServerAddCooldown_Implementation(FName spellName, float duration);

	UFUNCTION(BlueprintCallable, Category = Cooldowns)
		int32 CheckForCooldown(FName spellName);
	UFUNCTION(reliable, server, WithValidation)
		void ServerCheckForCooldown(FName spellName);
	virtual bool ServerCheckForCooldown_Validate(FName spellName);
	virtual void ServerCheckForCooldown_Implementation(FName spellName);

	UFUNCTION(BlueprintCallable, Category = Cooldowns)
		float CheckForCooldownValue(FName spellName);
	UFUNCTION(reliable, server, WithValidation)
		void ServerCheckForCooldownValue(FName spellName);
	virtual bool ServerCheckForCooldownValue_Validate(FName spellName);
	virtual void ServerCheckForCooldownValue_Implementation(FName spellName);

	UFUNCTION(BlueprintCallable, Category = Cooldowns)
		int32 UnreliableCheckForCD(FName spellName);
	UFUNCTION(BlueprintCallable, Category = Cooldowns)
		float UnreliableCheckForCDValue(FName spellName);

	UFUNCTION(BlueprintCallable, Category = Cooldowns)
		int32 CooldownCounter();
	void SortSpecificCooldown(FName spellName);

	// External effects management
	//UFUNCTION(BlueprintCallable, Category = EffectManagement)
	//	float CheckForCooldown(FName spellName);
	//UFUNCTION(reliable, server, WithValidation)
	//	void ServerCheckForCooldown(FName spellName);
	//virtual bool ServerCheckForCooldown_Validate(FName spellName);
	//virtual void ServerCheckForCooldown_Implementation(FName spellName);

	virtual void Tick(float DeltaSeconds) override;

private:
	TMultiMap<FName, float> cooldowns;
	TMultiMap<FString, int32> activeEffects;
};
