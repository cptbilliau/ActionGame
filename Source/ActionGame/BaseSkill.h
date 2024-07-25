// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "BaseSkill.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API ABaseSkill : public ABaseAbility
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Level")
	float BaseDamagePerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Level")
	float BaseHealingPerLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Level")
	float EnergyPerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Level")
	float DevotionScalingPerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Level")
	float MagicScalingPerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Level")
	float MightScalingPerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Level")
	float DevotionHealScalingPerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Level")
	float MagicHealScalingPerLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Level")
    float CooldownReductionPerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats | Level")
	TArray<FString> SkillDescriptionPerLevel;

protected:
	
	

	//void Set
};
