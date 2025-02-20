// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseItem::CalculateStatValue(EPlayerStats inStatType, float minPercent, float maxPercent, int ItemLevel,
	float& outStatValue, float& outPercentage)
{
	//Find map values
	float StatCoefficient = *StatCoefficientMap.Find(inStatType);
	float StatBase = *StatBaseMap.Find(inStatType);

	//Get random percent value
	float randomPercentValue = FMath::FRandRange(minPercent, maxPercent);

	float StatValue = ((randomPercentValue / 33) * (StatCoefficient * (ItemLevel/2 + 1)) + (StatBase * ItemLevel / 5)) + StatBase;
	
	//Calculate stat value
	outStatValue = StatValue;
	
	//Set Output Percentage
	outPercentage = randomPercentValue;
}



