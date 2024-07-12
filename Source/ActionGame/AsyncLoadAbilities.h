// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "BaseAbility.h"

#include "AsyncLoadAbilities.generated.h"

/**
 * , TSoftClassPtr<ABaseAbility>, AbilityIn, TSubclassOf<ABaseAbility>&, AbilityOut
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadSkillCompleted);

UCLASS()
class ACTIONGAME_API UAsyncLoadAbilities : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

protected:

	void HandleLoadCompleted(ABaseAbility AbilityToLoad, bool bSuccess);

public:

	UPROPERTY(BlueprintAssignable)
	FOnLoadSkillCompleted LoadSkill;



	//UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "LoadSkills")
		//static UAsyncLoadAbilities* LoadAbility(const UObject* WorldContextObject, TSoftClassPtr<ABaseAbility> AbilityIn);
	
private:

	UObject* WorldContextObject;
	TSoftClassPtr<ABaseAbility> LoadAbility;
};
