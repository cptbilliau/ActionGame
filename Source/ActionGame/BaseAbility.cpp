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

	if(BaseHealing > 0)
	{
		bDoesHeal = true;
	}
	else
	{
		bDoesHeal = false;
	}
}


void ABaseAbility::SetAbilityValues()
{
	float PlayerDevotion = *OwningPlayerStatMap.Find(EPlayerStats::E_Devotion);
	float PlayerMight = *OwningPlayerStatMap.Find(EPlayerStats::E_Might);
	float PlayerMagic = *OwningPlayerStatMap.Find(EPlayerStats::E_Magic);

	if (bDoesHeal)
	{
		AbilityHealing = BaseHealing ; //equation
		AbilityDamage = BaseDamage; //equation
	}
	else
	{
		AbilityDamage = BaseDamage; //equation
	}
	
}

// Called every frame
void ABaseAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

