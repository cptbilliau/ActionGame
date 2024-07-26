// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseSkill.h"

#include "SkillPicker.generated.h"


/**
 * 
 */
UCLASS()
class ACTIONGAME_API USkillPicker : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void LoadSkillAsset(TSoftClassPtr<ABaseSkill> InSkill, TSubclassOf<ABaseSkill>& OutSkill);
};
