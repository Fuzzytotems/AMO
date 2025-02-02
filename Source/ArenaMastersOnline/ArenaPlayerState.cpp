// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaMastersOnline.h"
#include "ArenaPlayerState.h"

// Add Cooldown
void AArenaPlayerState::AddCooldown(FName spellName, float cdLength)
{
	ServerAddCooldown(spellName, cdLength);
	ClientAddCooldown(spellName, cdLength);
}

void AArenaPlayerState::AddCooldownImplementation(FName spellName, float cdLength)
{
	cooldowns.Emplace(spellName, cdLength);

	SortSpecificCooldown(spellName);

	//if (current != cdLength)
	//{
	//	cooldowns.Emplace(spellName, current);
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Emplaced: %f"), current));
	//}
}

void AArenaPlayerState::ServerAddCooldown_Implementation(FName spellName, float cdLength)
{
	if (Role == ROLE_Authority)
	{
		AddCooldownImplementation(spellName, cdLength);
	}
}

void AArenaPlayerState::ClientAddCooldown_Implementation(FName spellName, float duration)
{
	if (Role < ROLE_Authority)
	{
		AddCooldownImplementation(spellName, duration);
	}
}

bool AArenaPlayerState::ClientAddCooldown_Validate(FName spellName, float duration)
{
	return true;
}

bool AArenaPlayerState::ServerAddCooldown_Validate(FName spellName, float cdLength)
{
	return true;
}

// Check For Cooldown
int32 AArenaPlayerState::CheckForCooldown(FName spellName)
{
	if (Role < ROLE_Authority)
	{
		ServerCheckForCooldown(spellName);
	}

	int32 result = 0;

	if (cooldowns.Contains(spellName))
	{
		for (auto it = cooldowns.CreateKeyIterator(spellName); it; ++it)
		{
			result++;
		}
	}

	return result;
}

void AArenaPlayerState::ServerCheckForCooldown_Implementation(FName spellName)
{
	if (Role == ROLE_Authority)
	{
		CheckForCooldown(spellName);
	}
}

bool AArenaPlayerState::ServerCheckForCooldown_Validate(FName spellName)
{
	return true;
}

// Check For Cooldown Value
float AArenaPlayerState::CheckForCooldownValue(FName spellName)
{
	if (Role < ROLE_Authority)
	{
		ServerCheckForCooldown(spellName);
	}

	float result = 0.f;
	int count = 0, tempCount = 0;

	/*for (auto it = cooldowns.CreateConstKeyIterator(spellName); it; ++it)
	{
		tempCount++;
		if (result == 0.f || result > it.Value())
		{
			result = it.Value();
			count = tempCount;
		}
	}*/

	result = *cooldowns.Find(spellName);

	return result;
}

void AArenaPlayerState::ServerCheckForCooldownValue_Implementation(FName spellName)
{
	if (Role == ROLE_Authority)
	{
		CheckForCooldownValue(spellName);
	}
}

bool AArenaPlayerState::ServerCheckForCooldownValue_Validate(FName spellName)
{
	return true;
}

int32 AArenaPlayerState::CooldownCounter()
{
	return cooldowns.Num();
}

void AArenaPlayerState::Tick(float DeltaSeconds)
{
	if (CooldownCounter() > 0)
	{
		FName currentKey;
		bool isMuddy = false;

		for (auto it = cooldowns.CreateIterator(); it; ++it)
		{
			if (currentKey == it.Key())
			{
				continue;
			}
			else
			{
				currentKey = it.Key();
			}

			it.Value() -= (DeltaSeconds * cdDilation);

			if (cdModifiers.Contains("ALL"))
			{
				it.Value() -= *cdModifiers.Find(it.Key());
			}
			
			while (cdModifiers.Contains(it.Key()))
			{
				it.Value() -= *cdModifiers.Find(it.Key());
				cdModifiers.Remove(it.Key());
			}

			if (it.Value() <= 0.f)
			{
				it.RemoveCurrent();
				isMuddy = true;
			}
		}

		if (isMuddy)
		{
			cooldowns.Compact();
			cooldowns.Shrink();
		}
	}

	cdModifiers.Empty();

	Super::Tick(DeltaSeconds);
}

void AArenaPlayerState::SortSpecificCooldown(FName spellName)
{
	float current = -1.f;
	for (auto it = cooldowns.CreateKeyIterator(spellName); it; ++it)
	{
		if (current > it.Value() || current == -1.f)
		{
			current = it.Value();
			it.RemoveCurrent();
			cooldowns.Emplace(spellName, current);
		}
	}
}

int32 AArenaPlayerState::UnreliableCheckForCD(FName spellName)
{
	int32 result = 0;

	if (cooldowns.Contains(spellName))
	{
		for (auto it = cooldowns.CreateKeyIterator(spellName); it; ++it)
		{
			result++;
		}
	}

	return result;

}

float AArenaPlayerState::UnreliableCheckForCDValue(FName spellName)
{
	float result = -1.f;
	int count = 0, tempCount = 0;

	if (cooldowns.Contains(spellName))
	{
		for (auto it = cooldowns.CreateKeyIterator(spellName); it; ++it)
		{
			if (result > it.Value() || result == -1.f)
			{
				result = it.Value();
			}
		}
	}

	//result = *cooldowns.Find(spellName);

	return result;
}

void AArenaPlayerState::ExposedRenamePlayer(FString NewName)
{
	if (Role == ROLE_Authority)
	{
		ServerExposedRenamePlayer(NewName);
		ClientExposedRenamePlayer(NewName);
	}
}

void AArenaPlayerState::ServerExposedRenamePlayer_Implementation(const FString& NewName)
{
	SetPlayerName(NewName);
}

bool AArenaPlayerState::ServerExposedRenamePlayer_Validate(const FString& NewName)
{
	return true;
}

void AArenaPlayerState::ClientExposedRenamePlayer_Implementation(const FString& NewName)
{
	SetPlayerName(NewName);
}

bool AArenaPlayerState::ClientExposedRenamePlayer_Validate(const FString& NewName)
{
	return true;
}

bool AArenaPlayerState::ModifySpecificCD(FName spellName, float duration)
{
	if (Role == ROLE_Authority)
	{
		MulticastModifySpecificCD(spellName, duration);
	}

	return true;
}

void AArenaPlayerState::MulticastModifySpecificCD_Implementation(FName spellName, float duration)
{
	cdModifiers.Add(spellName, duration);
}

bool AArenaPlayerState::MulticastModifySpecificCD_Validate(FName spellName, float duration)
{
	return true;
}

FString AArenaPlayerState::GetControllerNetworkID()
{
	SteamID = UniqueId->ToString();

	return SteamID;
}

void AArenaPlayerState::LearnNewSpell(FName newName, AActor* newSpell)
{
	if (!knownSpells.Find(newName))
	{
		if (ValidateSkillLearning(newName))
		{
			knownSpells.Add(newName, newSpell);

		}
	}
}

//void AArenaPlayerState::ServerLearnNewSpell_Implementation(FName newName, AActor* newSpell)
//{
//
//}
//
//bool AArenaPlayerState::ServerLearnNewSpell_Validate(FName newName, AActor* newSpell)
//{
//	return true;
//}
//
//void AArenaPlayerState::ClientLearnNewSpell_Implementation(FName newName, AActor* newSpell)
//{
//
//}
//
//bool AArenaPlayerState::ClientLearnNewSpell_Validate(FName newName, AActor* newSpell)
//{
//	return true;
//}

void AArenaPlayerState::KnowsSpell(FName newName, AActor*& newSpell)
{
}

//void AArenaPlayerState::ServerKnowsSpell_Implementation(FName newName, const AActor*& newSpell)
//{
//
//}
//
//bool AArenaPlayerState::ServerKnowsSpell_Validate(FName newName, AActor*& newSpell)
//{
//	return true;
//}
//
//void AArenaPlayerState::ClientKnowsSpell_Implementation(FName newName, AActor*& newSpell)
//{
//
//}
//
//bool AArenaPlayerState::ClientKnowsSpell_Validate(FName newName, AActor*& newSpell)
//{
//	return true;
//}

void AArenaPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(AArenaPlayerState, cdDilation);
}