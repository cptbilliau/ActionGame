// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StatStruct.h"

#include "BaseItem.generated.h"


UCLASS()
class ACTIONGAME_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Maps")
	TMap<EPlayerStats, float> StatCoefficientMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Maps")
	TMap<EPlayerStats, float> StatBaseMap;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, BlueprintPure)
	void CalculateStatValue(EPlayerStats  inStatType, float minPercent, float maxPercent, int ItemLevel, float& outStatValue, float& outPercentage);
};
