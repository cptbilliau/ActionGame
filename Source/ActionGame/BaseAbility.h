// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/Image.h"
#include "StatStruct.h"
#include "BaseAbility.generated.h"

enum class EAbilitySlot : uint8;

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	E_NONE UMETA(DisplayName = "NONE"),
	E_Projectile UMETA(DisplayName = "Projectile"),
	E_Melee UMETA(DisplayName = "Melee"),
	E_AOE UMETA(DisplayName = "AOE")
};

UENUM(BlueprintType)
enum class EAbilityTargetType :uint8
{
	E_NONE UMETA(DisplayName = "None"),
	E_Enemies UMETA(DisplayName = "Enemy"),
	E_Allies UMETA(DisplayName = "Allies"),
	E_AlliesAndEnemies UMETA(DisplayName = "Allies & Enemies")
};

UENUM(BlueprintType)
enum class EAbilityDamageType :uint8
{
	E_NONE UMETA(DisplayName = "None"),
	E_Physical UMETA(DisplayName = "Physical"),
	E_Magical UMETA(DisplayName = "Magical"),
};

class UProjectileMovementComponent;
UCLASS()
class ACTIONGAME_API ABaseAbility : public AActor
{
	GENERATED_BODY()
	

	
public:	
	// Sets default values for this actor's properties
	ABaseAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAbilityType AbilityType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAbilityTargetType AbilityTargetType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAbilityDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Base", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Base", meta = (AllowPrivateAccess = "true"))
	float ProjectileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Base", meta = (AllowPrivateAccess = "true"))
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Base", meta = (AllowPrivateAccess = "true"))
	float Radius;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Base", meta = (AllowPrivateAccess = "true"))
	float BaseCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Base", meta = (AllowPrivateAccess = "true"))
	float BaseDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Base", meta = (AllowPrivateAccess = "true"))
	float BaseHealing;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Stats | Base", meta = (AllowPrivateAccess = "true"))
	float EnergyCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Stats | Base", meta = (AllowPrivateAccess = "true"))
	float Lifetime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Scaling", meta = (AllowPrivateAccess = "true"))
	float MightScaling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Scaling", meta = (AllowPrivateAccess = "true"))
	float MagicScaling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Scaling", meta = (AllowPrivateAccess = "true"))
	float DevotionScaling;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Ability Stats | Scaling", meta = (AllowPrivateAccess = "true"))
 	float MagicHealScaling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Scaling", meta = (AllowPrivateAccess = "true"))
	float DevotionHealScaling;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Assets", meta = (AllowPrivateAccess = "true"))
	UTexture2D* SkillImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Assets", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AbilityAnim;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn=true))
	TArray<FReplicatedCurrentStat_Stat_Float> OwningPlayerStatMap;

	UPROPERTY(BlueprintReadWrite, Replicated, meta = (ExposeOnSpawn=true))
	EAbilitySlot AttachedSlot;

	UPROPERTY(BlueprintReadWrite, Category = "Ability Stats | Base", meta = (AllowPrivateAccess = "true", ExposeOnSpawn=true))
	int SkillLevel;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetAbilityDamage(float& DamageOut);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetAbilityHealing(float& HealingOut);
	
	void OnConstruction(const FTransform& Transform) override;
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float PlayerDevotion;
	float PlayerMight;
	float PlayerMagic;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovement;

	void SetAbilityValues();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
