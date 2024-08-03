// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbility.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABaseAbility::ABaseAbility()
{
	bReplicates = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	
	Lifetime = 20.0f;
}


void ABaseAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(ABaseAbility, AttachedSlot, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ABaseAbility, PlayerDevotion, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ABaseAbility, PlayerMagic, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ABaseAbility, PlayerMight, SharedParams);
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
	if (GetOwner() != nullptr)
	{

		FReplicatedCurrentStat_Stat_Float* FoundPlayerDevotion = OwningPlayerStatMap.FindByKey(EPlayerStats::E_Devotion);
		if (FoundPlayerDevotion)
		{
			PlayerDevotion = FoundPlayerDevotion->currentStat;
			
		}

		FReplicatedCurrentStat_Stat_Float* FoundPlayerMight = OwningPlayerStatMap.FindByKey(EPlayerStats::E_Might);
		if(FoundPlayerMight)
		{
			PlayerMight = FoundPlayerMight->currentStat;
		}

		FReplicatedCurrentStat_Stat_Float* FoundPlayerMagic = OwningPlayerStatMap.FindByKey(EPlayerStats::E_Magic);
		if(FoundPlayerMagic)
		{
			PlayerMagic = FoundPlayerMagic->currentStat;
		}

		DamageOut = BaseDamage+(PlayerDevotion*DevotionScaling/100)+(PlayerMagic*MagicScaling/100)+(PlayerMight*MightScaling/100);
	}
}

void ABaseAbility::GetAbilityHealing(float& HealingOut)
{
	FReplicatedCurrentStat_Stat_Float* FoundPlayerDevotion = OwningPlayerStatMap.FindByKey(EPlayerStats::E_Devotion);
	if (FoundPlayerDevotion)
	{
		PlayerDevotion = FoundPlayerDevotion->currentStat;
		
	}

	FReplicatedCurrentStat_Stat_Float* FoundPlayerMight = OwningPlayerStatMap.FindByKey(EPlayerStats::E_Might);
	if(FoundPlayerMight)
	{
		PlayerMight = FoundPlayerMight->currentStat;
	}

	FReplicatedCurrentStat_Stat_Float* FoundPlayerMagic = OwningPlayerStatMap.FindByKey(EPlayerStats::E_Magic);
	if(FoundPlayerMagic)
	{
		PlayerMagic = FoundPlayerMagic->currentStat;
	}

	if (GetOwner() != nullptr)
	{
		
		HealingOut = BaseHealing+(PlayerDevotion*DevotionHealScaling/100)+(PlayerMagic*MagicHealScaling/100);
	} 
}




// Called every frame
void ABaseAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

