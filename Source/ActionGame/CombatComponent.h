// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseAbility.h"
#include "BaseSkill.h"
#include "BaseBasicAttack.h"
#include "ActionGameCharacter.h"
#include "StatStruct.h"
#include "AbilityDamage.h"
#include "BaseMovementSkill.h"
#include "StatStruct.h"
#include "GameFramework/DamageType.h"
#include "Delegates/DelegateCombinations.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"


#include "CombatComponent.generated.h"


UENUM(BlueprintType)
enum class EPlayerClass : uint8
{
	E_Caster UMETA(DisplayName = "Caster"),
	E_Brawler UMETA(DisplayName = "Brawler"),
	E_Duelist UMETA(DisplayName = "Duelist"),
};




DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentStatChanged, EPlayerStats, outStat, float, outFloat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetCooldownTimeRemaining, EAbilitySlot, outSlot, float, outFloat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBaseStatChanged, EPlayerStats, outStat, float, outFloat);
class AActionGameCharacter;

//UCLASS ABa
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONGAME_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this component's properties
	UCombatComponent();

	UPROPERTY(BlueprintAssignable)
	FOnCurrentStatChanged CurrentStatChanged;

	UPROPERTY(BlueprintAssignable)
	FGetCooldownTimeRemaining CooldownTimeRemaining;

	UPROPERTY(BlueprintAssignable)
	FOnBaseStatChanged BaseStatChanged;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AbilityObjects | StoredAbility")
	TArray<TSubclassOf<ABaseAbility>> CachedAbilities;
	
#pragma region Ability Functions
	UFUNCTION(BlueprintCallable, Category = "CombatComponent | Abilities")
	void SetAbilityOnCooldown(float inCooldown, EAbilitySlot slot);

	UFUNCTION(BlueprintPure, Category = "CombatComponent | Abilities")
	void GetAbilityCooldownTimer(EAbilitySlot slot, float& TimeLeft) const;

	UFUNCTION(BlueprintPure, Category = "CombatComponent | Abilities")
	TSubclassOf<ABaseAbility> GetAbilityBySlot(EAbilitySlot slot) const;

	UFUNCTION(BlueprintPure, Category = "CombatComponent | Abilities")
	void GetAbilityImageBySlot(EAbilitySlot slot, UTexture2D*& OutImage);

	UFUNCTION()
	void SetAbilityOffCooldown(EAbilitySlot slot);
#pragma endregion

#pragma region Stat Functions
	UFUNCTION (BlueprintPure, Category = "CombatComponent | Stats")
	float GetCurrentStatValue(EPlayerStats Stat);

	UFUNCTION(BlueprintPure, Category = "CombatComponent | Stats")
	float GetMaxStatValue(EPlayerStats Stat);

	UFUNCTION(BlueprintPure, Category = "CombatComponent | Stats")
	float GetBaseStatValue(EPlayerStats Stat);


	UFUNCTION(BlueprintCallable, Category = "CombatComponent | Stats")
	void ModifyBaseStatValue(EPlayerStats inStat, float ModifyBy);
	
	UFUNCTION(BlueprintAuthorityOnly, Category = "CombatComponent | Class")
	float GetClassRegenRate(EPlayerClass inClass);

	UFUNCTION(BlueprintCallable, Category = "CombatComponent | Stats")
	void SetCurrentStatValue(EPlayerStats Stat, float InStat);

	UFUNCTION(BlueprintCallable, Category = "CombatComponent | Stats")
	void SetMaxStatValue(EPlayerStats Stat, float InStat);

	UFUNCTION(BlueprintCallable, Category = "CombatComponent | Stats")
	void SetBaseStatValue(EPlayerStats Stat, float InStat);

	UFUNCTION(BlueprintCallable, Category = "CombatComponent | Stats")
	void ModifyCurrentStatValue(EPlayerStats Stat, float InStat);

	UFUNCTION(BlueprintCallable, Category = "CombatComponent | Stats")
	void TakeDamage(float InDamage, TSubclassOf<UDamageType> DamageType, float& DamageTaken);

#pragma endregion


	//Stat

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AbilityObjects | Basic")
	TSoftClassPtr<ABaseBasicAttack> BasicAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AbilityObjects | Movement")
	TSoftClassPtr<ABaseMovementSkill> MovementSkill;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AbilityObjects | Skills")
	TSoftClassPtr<ABaseSkill> SkillSlot1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AbilityObjects | Skills")
	TSoftClassPtr<ABaseSkill> SkillSlot2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AbilityObjects | Skills")
	TSoftClassPtr<ABaseSkill> SkillSlot3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats | Class")
	EPlayerClass PlayerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Team")
	int Team;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "AbilityObjects ")
	FWeaponItemData MainWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats ")
	TMap<EPlayerStats, FStatStruct> PlayerStatMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats ")
	TMap<EPlayerStats, float> CurrentPlayerStatMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TMap<TSoftClassPtr<ABaseSkill>, int> SkillLevelMap;

	UFUNCTION()
	void OnRep_CurrentStatMapWorkaround();

	UFUNCTION()
	void OnRep_StatMapWorkAround();
		
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentStatMapWorkaround)
	TArray<FReplicatedCurrentStat_Stat_Float> MapCurrentStatWorkaroundArray;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StatMapWorkAround)
	TArray<FReplicatedBaseStat_Stat_Float> StatMapWorkaroundArray;

	void ReplicateCurrentStatMapWorkAround();
	
	void ReplicatePlayerStatMapWorkAround();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void HandleAbilityUsage(FTransform SpawnTransform, EAbilitySlot AttachedSlot, AActor* Owner,
		APawn* Instigator, const TArray<FReplicatedCurrentStat_Stat_Float>& CurrentPlayerStats, int SkillLevel, TSubclassOf<ABaseAbility> AbilityToSpawn);

	
private:
	
	

};
