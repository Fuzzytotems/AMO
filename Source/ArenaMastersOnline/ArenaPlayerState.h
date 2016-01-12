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
		bool ModifySpecificCD(FName spellName, float duration);
	UFUNCTION(reliable, NetMulticast, WithValidation)
		void MulticastModifySpecificCD(FName spellName, float duration);
	virtual bool MulticastModifySpecificCD_Validate(FName spellName, float duration);
	virtual void MulticastModifySpecificCD_Implementation(FName spellName, float duration);

	UFUNCTION(BlueprintCallable, Category = Cooldowns)
		int32 UnreliableCheckForCD(FName spellName);
	UFUNCTION(BlueprintCallable, Category = Cooldowns)
		float UnreliableCheckForCDValue(FName spellName);

	UFUNCTION(BlueprintCallable, Category = Cooldowns)
		int32 CooldownCounter();
	void SortSpecificCooldown(FName spellName);

	UFUNCTION(BlueprintCallable, Category = General)
		void ExposedRenamePlayer(FString NewName);
	UFUNCTION(reliable, server, WithValidation)
		void ServerExposedRenamePlayer(const FString& NewName);
	UFUNCTION(reliable, Client, WithValidation)
		void ClientExposedRenamePlayer(const FString& NewName);
	virtual void ServerExposedRenamePlayer_Implementation(const FString& NewName);
	virtual bool ServerExposedRenamePlayer_Validate(const FString& NewName);
	virtual void ClientExposedRenamePlayer_Implementation(const FString& NewName);
	virtual bool ClientExposedRenamePlayer_Validate(const FString& NewName);

	UFUNCTION(BlueprintCallable, Category = Online)
		FString GetControllerNetworkID();

	UFUNCTION(BlueprintImplementableEvent, Category = Spells)
		bool ValidateSkillLearning(FName newName);

	UFUNCTION(BlueprintCallable, Category = Spells)
		void LearnNewSpell(FName newName, AActor* newSpell);
	//UFUNCTION(reliable, server, WithValidation)
	//	void ServerLearnNewSpell(FName newName, AActor* newSpell);
	//UFUNCTION(reliable, Client, WithValidation)
	//	void ClientLearnNewSpell(FName newName, AActor* newSpell);
	//virtual void ServerLearnNewSpell_Implementation(FName newName, AActor* newSpell);
	//virtual bool ServerLearnNewSpell_Validate(FName newName, AActor* newSpell);
	//virtual void ClientLearnNewSpell_Implementation(FName newName, AActor* newSpell);
	//virtual bool ClientLearnNewSpell_Validate(FName newName, AActor* newSpell);

	UFUNCTION(BlueprintCallable, Category = Spells)
		void KnowsSpell(FName newName, AActor*& newSpell);
	//UFUNCTION(reliable, server, WithValidation)
	//	void ServerKnowsSpell(FName newName, const AActor*& newSpell);
	//UFUNCTION(reliable, Client, WithValidation)
	//	void ClientKnowsSpell(FName newName, const AActor*& newSpell);
	//virtual void ServerKnowsSpell_Implementation(FName newName, AActor*& newSpell);
	//virtual bool ServerKnowsSpell_Validate(FName newName, AActor*& newSpell);
	//virtual void ClientKnowsSpell_Implementation(FName newName, AActor*& newSpell);
	//virtual bool ClientKnowsSpell_Validate(FName newName, AActor*& newSpell);

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
		FString SteamID;

	UPROPERTY(BlueprintReadWrite, Replicated)
		float cdDilation = 1.f;

private:
	TMultiMap<FName, float> cooldowns;
	TMultiMap<FString, int32> activeEffects;
	TMap<FName, AActor*> knownSpells;
	TMultiMap<FName, float> cdModifiers;
};
