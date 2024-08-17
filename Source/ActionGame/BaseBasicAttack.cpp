// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBasicAttack.h"

#include "CombatComponent.h"

void ABaseBasicAttack::BeginPlay()
{
	setStats();
	Super::BeginPlay();

	
}

void ABaseBasicAttack::setStats()
{
	AActor* InstigatorPawn = GetInstigator();

	if (InstigatorPawn != nullptr)
	{
		AActionGameCharacter* Character = Cast<AActionGameCharacter>(InstigatorPawn);
		if(Character != nullptr)
			{
				UCombatComponent* PlayerCombatComponent = Character->FindComponentByClass<UCombatComponent>();
				if(PlayerCombatComponent != nullptr)
			{
					WeaponItemData = PlayerCombatComponent->MainWeapon;
					Range = WeaponItemData.Range;
					SizeAngle = WeaponItemData.SizeAngle;
					BaseCooldown = WeaponItemData.Cooldown;
					BaseDamage = WeaponItemData.BaseDamage; 
					DevotionScaling = WeaponItemData.DevotionScaling;
					MightScaling = WeaponItemData.MightScaling;
					MagicScaling = WeaponItemData.MagicScaling;
					FString healthMessage = FString::Printf(TEXT("Weapon Damage is: %f."), BaseDamage);
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
					
			}
		}
	}

	
}

