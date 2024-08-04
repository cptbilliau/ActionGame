// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatStruct.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class EAbilitySlot : uint8
{
	E_NONE UMETA(DisplayName = "NONE"),
	E_BasicAttack UMETA(DisplayName = "Basic Attack"),
	E_Slot1 UMETA(DisplayName = "Slot 1"),
	E_Slot2 UMETA(DisplayName = "Slot 2"),
	E_Slot3 UMETA(DisplayName = "Slot 3"),
	E_MovementSlot UMETA(DisplayName = "Movement Ability"),
};

UENUM(BlueprintType)
enum class EPlayerStats : uint8
{
	E_HP UMETA(DisplayName = "HP"),
	E_Energy UMETA(DisplayName = "Energy"),
	E_Speed UMETA(DisplayName = "Speed"),
	E_Dexterity UMETA(DisplayName = "Dexterity"),
	E_Might UMETA(DisplayName = "Might"),
	E_Magic UMETA(DisplayName = "Magic"),
	E_Devotion UMETA(DisplayName = "Devotion"),
	E_Armour UMETA(DisplayName = "Armour"),
	E_Resistance UMETA(DisplayName = "Resistance"),
};

USTRUCT(BlueprintType)
struct ACTIONGAME_API FStatStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float base;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float max;
	FStatStruct();
	~FStatStruct();
};

USTRUCT(BlueprintType)
struct ACTIONGAME_API FItemStatStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerStats  stat;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float statValue;
	
	
	FItemStatStruct();
	~FItemStatStruct();
};

USTRUCT(BlueprintType)
struct ACTIONGAME_API FEquipmentStatStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerStats stat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float minPercent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxPercent;
	FEquipmentStatStruct();
	~FEquipmentStatStruct();
};

USTRUCT(BlueprintType)
struct FReplicatedCurrentStat_Stat_Float
{
	UPROPERTY(BlueprintReadOnly)
	EPlayerStats Stat;
	UPROPERTY(BlueprintReadOnly)
	float currentStat;
	bool operator==(const EPlayerStats& StatType) const
	{
		return Stat == StatType; 
	}
	GENERATED_BODY()
	FReplicatedCurrentStat_Stat_Float();
	~FReplicatedCurrentStat_Stat_Float();
};
USTRUCT(BlueprintType)
struct FReplicatedBaseStat_Stat_Float
{
	UPROPERTY(BlueprintReadOnly)
	EPlayerStats Stat;
	UPROPERTY(BlueprintReadOnly)
	FStatStruct BaseStat;
	bool operator==(const EPlayerStats& StatType) const
	{
		return Stat == StatType; 
	}
	GENERATED_BODY()
	FReplicatedBaseStat_Stat_Float();
	~FReplicatedBaseStat_Stat_Float();
};


