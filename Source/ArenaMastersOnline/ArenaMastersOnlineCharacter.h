// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Spellbook.h"
#include "GameFramework/Character.h"
#include "ArenaMastersOnlineCharacter.generated.h"

UENUM(BlueprintType)
namespace EResourceType
{
	enum ResourceType
	{
		RT_Mana			UMETA(DisplayName = "Mana"),
		RT_Rage			UMETA(DisplayName = "Rage"),
		RT_Energy		UMETA(DisplayName = "Energy"),
		RT_Momentum		UMETA(DisplayName = "Momentum"),
		RT_Corruption	UMETA(DisplayName = "Corruption"),

		RT_MAX			UMETA(Hidden),
	};
}

UCLASS(config=Game)
class AArenaMastersOnlineCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AArenaMastersOnlineCharacter(const FObjectInitializer& ObjectInitializer);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Health and Resource variables
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, Category = Stats)
		float speedFactor;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		float baseMaxHealth;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		float maxHealth;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		float currentHealth;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		float excessHealth;

	UPROPERTY(BlueprintReadWrite, Category = Stats)
		float baseMaxResource;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		float maxResource;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		float currentResource;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		float excessResource;

	UPROPERTY(BlueprintReadWrite, Category = Stats)
		bool bIsImmortal;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		bool bIsDead;

	UPROPERTY(BlueprintReadWrite, Category = Stats)
		ASpellbook* spellbook;

	//UFUNCTION(Exec)
	//	void AttemptCastSpell(int32 SpellIndex);
	UFUNCTION(BlueprintCallable, Category = Stats)
		bool IsDead();

	void InitStats();
	
	void TickRegen(float DeltaSeconds);
};

inline bool AArenaMastersOnlineCharacter::IsDead()
{
	return bIsDead;
}