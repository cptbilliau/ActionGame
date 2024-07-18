// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbility.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABaseAbility::ABaseAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	
	Lifetime = 20.0f;
}



void ABaseAbility::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

		
	
}

// Called when the game starts or when spawned
void ABaseAbility::BeginPlay()
{
	Super::BeginPlay();

	
}



void ABaseAbility::GetAbilityDamage(float& DamageOut)
{
	float PlayerDevotion = *OwningPlayerStatMap.Find(EPlayerStats::E_Devotion);
	float PlayerMight = *OwningPlayerStatMap.Find(EPlayerStats::E_Might);
	float PlayerMagic = *OwningPlayerStatMap.Find(EPlayerStats::E_Magic);
	
	DamageOut = BaseDamage+(PlayerDevotion*DevotionScaling/100)+(PlayerMagic*MagicScaling/100)+(PlayerMight*MightScaling/100);

}

void ABaseAbility::GetAbilityHealing(float& HealingOut)
{
	float PlayerDevotion = *OwningPlayerStatMap.Find(EPlayerStats::E_Devotion);
	float PlayerMight = *OwningPlayerStatMap.Find(EPlayerStats::E_Might);
	float PlayerMagic = *OwningPlayerStatMap.Find(EPlayerStats::E_Magic);

	HealingOut = BaseHealing+(PlayerDevotion*DevotionHealScaling/100)+(PlayerMagic*MagicHealScaling/100);
}


// Called every frame
void ABaseAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

