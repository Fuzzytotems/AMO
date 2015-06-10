// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Spell.generated.h"

UENUM(BlueprintType)
namespace EAimingType
{
	enum AimingType
	{
		AT_SkillShot		UMETA(DisplayName = "Skill Shot"),
		AT_MouseOver		UMETA(DisplayName = "Mouse Over"),
		AT_HitScan			UMETA(DisplayName = "Hit Scan"),
		AT_AutoTarget		UMETA(DisplayName = "Auto Target"),
		AT_Toggled			UMETA(DisplayName = "Toggled"),
		AT_GroundTargeted	UMETA(DisplayName = "Ground Targeted"),
		AT_Passive			UMETA(DisplayName = "Passive"),
		AT_SmartTarget		UMETA(DisplayName = "Frame Targeted"),

		AT_MAX				UMETA(Hidden),
	};
}

UENUM(BlueprintType)
namespace ECastingType
{
	enum CastingType
	{
		CT_Cast				UMETA(DisplayName = "Cast"),
		CT_Channeled		UMETA(DisplayName = "Channeled"),
		CT_Charged			UMETA(DisplayName = "Charged"),

		CT_MAX				UMETA(Hidden),
	};
}

UENUM(BlueprintType)
namespace EDisableType
{
	enum DisableType
	{
		DT_Silence			UMETA(DisplayName = "Silence"),
		DT_Disarm			UMETA(DisplayName = "Disarm"),
		DT_Either			UMETA(DisplayName = "Either"),
		DT_Both				UMETA(DisplayName = "Both"),

		DT_MAX				UMETA(Hidden),
	};
}

UENUM(BlueprintType)
namespace EMagicSchool
{
	enum MagicSchool
	{
		MS_Holy				UMETA(DisplayName = "Holy"),
		MS_Unholy			UMETA(DisplayName = "Unholy"),
		MS_Fire				UMETA(DisplayName = "Fire"),
		MS_Cold				UMETA(DisplayName = "Cold"),
		MS_Nature			UMETA(DisplayName = "Nature"),
		MS_Universal		UMETA(DisplayName = "Universal"),

		MS_MAX				UMETA(Hidden),
	};
}

UCLASS()
class ARENAMASTERSONLINE_API ASpell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpell();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
		float BaseCastTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		TEnumAsByte<EAimingType::AimingType> BaseAimType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		TEnumAsByte<ECastingType::CastingType> BaseCastingType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		TEnumAsByte<EDisableType::DisableType> BaseDisableType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		bool bBaseIsBouncy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		bool bBaseCastWhileMoving;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
		float BaseMinDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
		float BaseCooldown;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
		float BaseMaxDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
		int32 BaseResourceCost;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
		int32 BaseMaxCharges;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
		int32 BaseSpellLifetime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
		TArray<TEnumAsByte<EMagicSchool::MagicSchool>> BaseMagicSchools;

	UPROPERTY(BlueprintReadWrite, Category = Stats)
		float MinDamage;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		float MaxDamage;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		float CooldownElapsed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
		float Cooldown;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
		bool bIsOnCooldown;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		float CastTime;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		int32 ResourceCost;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		TEnumAsByte<EAimingType::AimingType> AimType;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		TEnumAsByte<ECastingType::CastingType> CastingType;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		TEnumAsByte<EDisableType::DisableType> DisableType;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		bool bIsBouncy;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		bool bCastWhileMoving;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		TArray<TEnumAsByte<EMagicSchool::MagicSchool>> MagicSchools;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		int32 MaxCharges;
	UPROPERTY(BlueprintReadWrite, Category = Stats)
		int32 CurrentCharges;
	// This is the duration the projectile lasts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float SpellLifetime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		TSubclassOf<class AActor> SpellEffect;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Stats)
		bool CastSpell(FHitResult HitResult, AActor* Target);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Stats)
		void MouseOverTest();
	UFUNCTION(BlueprintCallable, Category = Stats)
		bool ReduceCD(float DeltaTime);
	UFUNCTION(BlueprintCallable, Category = Stats)
		void InitStats();
};
