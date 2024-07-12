// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "AbilityDamage.generated.h"

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	E_NONE UMETA(DisplayName = "NONE"),
	E_Physical UMETA(DisplayName = "Physical"),
	E_Magical  UMETA(DisplayName = "Magical"),
	E_Healing UMETA(DisplayName = "Healing")
};

UCLASS()
class ACTIONGAME_API UAbilityDamage : public UDamageType
{
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDamageType DamageType;

	GENERATED_BODY()
	
};
