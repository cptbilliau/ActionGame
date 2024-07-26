// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "GameFramework/Actor.h"
#include "BaseBasicAttack.h"
#include "ActionGameCharacter.h"
#include "Chaos/Deformable/Utilities.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

FTimerHandle BasicAttackCooldown;
FTimerHandle Slot1Cooldown;
FTimerHandle Slot2Cooldown;
FTimerHandle Slot3Cooldown;
struct FStatStruct;
class UDamageType;

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
   PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	
	// ...
	
}


void UCombatComponent::SetAbilityOnCooldown(float inCooldown, EAbilitySlot slot)
{
	
	
	FTimerDelegate Delagate;
	Delagate.BindUFunction(this, "SetAbilityOffCooldown", slot);

	switch(slot)
	{
	case EAbilitySlot::E_NONE:
		//throw error do nothing
		break;
	case EAbilitySlot::E_BasicAttack:
				
		float RealCooldown;
		if (PlayerStatMap.Contains(EPlayerStats::E_Dexterity)) 
		{
			float PlayerDex = CurrentPlayerStatMap[EPlayerStats::E_Dexterity];
			//Calculate Real Cooldown
			RealCooldown = inCooldown * (100 / (100 + PlayerDex));

			GetWorld()->GetTimerManager().SetTimer(BasicAttackCooldown, Delagate, RealCooldown, true);
		}
		
		break;
	case EAbilitySlot::E_Slot1:

		//SetSlot1Cooldowntimer

		GetWorld()->GetTimerManager().SetTimer(Slot1Cooldown, Delagate, inCooldown, true);
		break;
	case EAbilitySlot::E_Slot2:
		//SetSlot2Cooldowntimer
		GetWorld()->GetTimerManager().SetTimer(Slot2Cooldown, Delagate, inCooldown, true);
		break;
	case EAbilitySlot::E_Slot3:
		//SetSlot3Cooldowntimer
		GetWorld()->GetTimerManager().SetTimer(Slot3Cooldown, Delagate, inCooldown, true);
		break;
	case EAbilitySlot::E_MovementSlot:
		//SetMovementSlotCooldown
		break;
	}
	
	
	
}

void UCombatComponent::GetAbilityCooldownTimer(EAbilitySlot slot, float& TimeLeft) const
{
	switch (slot)
	{
	case EAbilitySlot::E_NONE:
		//throw error do nothing
		break;
	case EAbilitySlot::E_BasicAttack:

		TimeLeft = GetWorld()->GetTimerManager().GetTimerRemaining(BasicAttackCooldown);
		CooldownTimeRemaining.Broadcast(slot, TimeLeft);
		break;

	case EAbilitySlot::E_Slot1:
		//SetSlot1Cooldowntimer
		TimeLeft = GetWorld()->GetTimerManager().GetTimerRemaining(Slot1Cooldown);
		CooldownTimeRemaining.Broadcast(slot, TimeLeft);
		break;
	case EAbilitySlot::E_Slot2:
		//SetSlot2Cooldowntimer
		TimeLeft = GetWorld()->GetTimerManager().GetTimerRemaining(Slot2Cooldown);
		CooldownTimeRemaining.Broadcast(slot, TimeLeft);
		break;
	case EAbilitySlot::E_Slot3:
		//SetSlot3 Cooldown timer
		TimeLeft = GetWorld()->GetTimerManager().GetTimerRemaining(Slot3Cooldown);
		CooldownTimeRemaining.Broadcast(slot, TimeLeft);
		break;
	case EAbilitySlot::E_MovementSlot:
		//SetMovementSlotCooldown
		break;
	}
	
}

void UCombatComponent::GetAbilityBySlot(EAbilitySlot slot, TSubclassOf<ABaseAbility>& OutAbility)
{
	switch (slot)
	{
	case EAbilitySlot::E_NONE:
		//throw error do nothing
		break;
	case EAbilitySlot::E_BasicAttack:
		
		OutAbility = BasicAttack.LoadSynchronous();
		break;

	case EAbilitySlot::E_Slot1:
		//SetSlot1Cooldowntimer
		OutAbility = SkillSlot1.LoadSynchronous();
		break;
	case EAbilitySlot::E_Slot2:
		OutAbility = SkillSlot2.LoadSynchronous();
		break;
	case EAbilitySlot::E_Slot3:
		OutAbility = SkillSlot3.LoadSynchronous();
		break;
	case EAbilitySlot::E_MovementSlot:
		//LoadMovementSlot
		break;
	}
}

void UCombatComponent::GetAbilityImageBySlot(EAbilitySlot slot, UTexture2D*& OutImage)
{
	switch (slot)
	{
	case EAbilitySlot::E_NONE:
		//throw error do nothing
		break;
	case EAbilitySlot::E_BasicAttack:

		OutImage = BasicAttack->GetDefaultObject<ABaseBasicAttack>()->SkillImage;
		break;

	case EAbilitySlot::E_Slot1:
		//SetSlot1Cooldowntimer
		OutImage = SkillSlot1->GetDefaultObject<ABaseSkill>()->SkillImage;
		break;
	case EAbilitySlot::E_Slot2:
		//SetSlot2Cooldowntimer
		OutImage = SkillSlot2->GetDefaultObject<ABaseSkill>()->SkillImage;
		break;
	case EAbilitySlot::E_Slot3:
		//SetSlot3Cooldowntimer
		OutImage = SkillSlot3->GetDefaultObject<ABaseSkill>()->SkillImage;
		break;
	case EAbilitySlot::E_MovementSlot:
		//GetMovementImage
		break;
	}

}


void UCombatComponent::SetAbilityOffCooldown(EAbilitySlot slot)
{
	switch (slot)
	{
	case EAbilitySlot::E_NONE:
		//throw error do nothing
		break;
	case EAbilitySlot::E_BasicAttack:
	
		GetWorld()->GetTimerManager().ClearTimer(BasicAttackCooldown);
		break;
	
	case EAbilitySlot::E_Slot1:
		//SetSlot1Cooldowntimer
		GetWorld()->GetTimerManager().ClearTimer(Slot1Cooldown);
		break;
	case EAbilitySlot::E_Slot2:
		//SetSlot2Cooldowntimer
		GetWorld()->GetTimerManager().ClearTimer(Slot2Cooldown);
		break;
	case EAbilitySlot::E_Slot3:
		//SetSlot3Cooldowntimer
		GetWorld()->GetTimerManager().ClearTimer(Slot3Cooldown);
		break;
	case EAbilitySlot::E_MovementSlot:
		//SetMovementSlotCooldown
		break;
	}
}






#pragma region SetRegion


void UCombatComponent::SetMaxStatValue(EPlayerStats Stat, float inStat)
{
	FStatStruct PlayerStat = PlayerStatMap[Stat];

	PlayerStat.max = inStat;

}



void UCombatComponent::SetBaseStatValue(EPlayerStats Stat, float inStat)
{
	FStatStruct* PlayerStat = PlayerStatMap.Find(Stat);

	PlayerStat->base = inStat;
	
	PlayerStatMap.Add(Stat, *PlayerStat);

}
void UCombatComponent::ModifyBaseStatValue(EPlayerStats inStat, float ModifyBy)
{
	FStatStruct* Stat = PlayerStatMap.Find(inStat);
	
	float value = Stat->base + ModifyBy;

	float ClampedValue = FMath::Clamp(value, 0.0f, GetMaxStatValue(inStat));
	
	Stat->base = ClampedValue;
	PlayerStatMap.Add(inStat, *Stat);

	BaseStatChanged.Broadcast(inStat, ModifyBy);
}	

void UCombatComponent::ModifyCurrentStatValue(EPlayerStats Stat, float InReduction)
{
	float value = GetCurrentStatValue(Stat) + InReduction;

	float ClampedValue = FMath::Clamp(value, 0.0f, GetMaxStatValue(Stat));
	
	SetCurrentStatValue(Stat, ClampedValue);
}

void UCombatComponent::TakeDamage(float InDamage, TSubclassOf<UDamageType> DamageType, float& DamageTaken)
{
	if(DamageType == nullptr)
	{
		
	}
	else if (DamageType->GetDefaultObject<UAbilityDamage>()->DamageType == EDamageType::E_Magical)
	{

		FStatStruct PlayerStat = PlayerStatMap[EPlayerStats::E_HP];
		float playerResistance = *CurrentPlayerStatMap.Find(EPlayerStats::E_Resistance);
		//need to add resistance calculation
		float calculatedDamage = ((100 * InDamage)/(playerResistance + 100));
		float value = GetCurrentStatValue(EPlayerStats::E_HP) - calculatedDamage;

		float ClampedValue = FMath::Clamp(value, 0.0f, GetBaseStatValue(EPlayerStats::E_HP));
		DamageTaken = calculatedDamage;
		SetCurrentStatValue(EPlayerStats::E_HP, ClampedValue);
			
	}
	else if (DamageType->GetDefaultObject<UAbilityDamage>()->DamageType == EDamageType::E_Physical)
	{
		FStatStruct PlayerStat = PlayerStatMap[EPlayerStats::E_HP];
		
		float playerArmour = *CurrentPlayerStatMap.Find(EPlayerStats::E_Armour);
		//need to add amour calculation
		float calculatedDamage = ((100 * InDamage)/(playerArmour + 100));
		float value = GetCurrentStatValue(EPlayerStats::E_HP) - calculatedDamage;
		
		float ClampedValue = FMath::Clamp(value, 0.0f, GetBaseStatValue(EPlayerStats::E_HP));
		DamageTaken = calculatedDamage;
		SetCurrentStatValue(EPlayerStats::E_HP, ClampedValue);

	}
	else if (DamageType->GetDefaultObject<UAbilityDamage>()->DamageType == EDamageType::E_Healing)
	{
		FStatStruct PlayerStat = PlayerStatMap[EPlayerStats::E_HP];
		//need to add amour calculation
		float value = GetCurrentStatValue(EPlayerStats::E_HP) + InDamage;
		
		float ClampedValue = FMath::Clamp(value, 0.0f, GetBaseStatValue(EPlayerStats::E_HP));

		DamageTaken = InDamage;
		SetCurrentStatValue(EPlayerStats::E_HP, ClampedValue);

	}
}

void UCombatComponent::SetCurrentStatValue(EPlayerStats Stat, float inStat)
{
	CurrentStatChanged.Broadcast(Stat, inStat);

	CurrentPlayerStatMap.Add(Stat, inStat);

}

#pragma endregion
/*

GET STAT
*/
#pragma region Get Stat
float UCombatComponent::GetCurrentStatValue(EPlayerStats Stat)
{
	switch (Stat)
	{
	case EPlayerStats::E_HP:
		if (CurrentPlayerStatMap.Contains(EPlayerStats::E_HP))
		{

			return CurrentPlayerStatMap[EPlayerStats::E_HP];
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Energy:
		if (CurrentPlayerStatMap.Contains(EPlayerStats::E_Energy))
		{

			return CurrentPlayerStatMap[EPlayerStats::E_Energy];
		}
		else

			return 0.0f;
		break;
	case EPlayerStats::E_Speed:
		if (CurrentPlayerStatMap.Contains(EPlayerStats::E_Speed))
		{
			
			return CurrentPlayerStatMap[EPlayerStats::E_Speed];
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Dexterity:
		if (CurrentPlayerStatMap.Contains(EPlayerStats::E_Dexterity))
		{

			return CurrentPlayerStatMap[EPlayerStats::E_Dexterity];
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Might:
		if (CurrentPlayerStatMap.Contains(EPlayerStats::E_Might))
		{

			return CurrentPlayerStatMap[EPlayerStats::E_Might];
		}
			return 0.0f;
		break;
	case EPlayerStats::E_Magic:
		if (CurrentPlayerStatMap.Contains(EPlayerStats::E_Magic))
		{
			return CurrentPlayerStatMap[EPlayerStats::E_Magic];
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Devotion:
		if (CurrentPlayerStatMap.Contains(EPlayerStats::E_Devotion))
		{
			return CurrentPlayerStatMap[EPlayerStats::E_Devotion];
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Armour:
		if (CurrentPlayerStatMap.Contains(EPlayerStats::E_Armour))
		{
			return CurrentPlayerStatMap[EPlayerStats::E_Armour];
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Resistance:
		if (CurrentPlayerStatMap.Contains(EPlayerStats::E_Resistance))
		{
			return CurrentPlayerStatMap[EPlayerStats::E_Resistance];
		}
		else
			return 0.0f;
		break;
	default:
		return 0.0f;
		break;
	}


}
float UCombatComponent::GetMaxStatValue(EPlayerStats Stat)
{

	switch (Stat)
	{
	case EPlayerStats::E_HP:
		if (PlayerStatMap.Contains(EPlayerStats::E_HP))
		{
			FStatStruct PlayerEnergy = PlayerStatMap[EPlayerStats::E_HP];
			return PlayerEnergy.max;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Energy:
		if (PlayerStatMap.Contains(EPlayerStats::E_Energy))
		{
			FStatStruct PlayerEnergy = PlayerStatMap[EPlayerStats::E_Energy];
			return PlayerEnergy.max;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Speed:
		if (PlayerStatMap.Contains(EPlayerStats::E_Speed))
		{
			FStatStruct PlayerDex = PlayerStatMap[EPlayerStats::E_Speed];
			return PlayerDex.max;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Dexterity:
		if (PlayerStatMap.Contains(EPlayerStats::E_Dexterity))
		{
			FStatStruct PlayerDex = PlayerStatMap[EPlayerStats::E_Dexterity];
			return PlayerDex.max;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Might:
		if (PlayerStatMap.Contains(EPlayerStats::E_Might))
		{
			FStatStruct PlayerEnergy = PlayerStatMap[EPlayerStats::E_Might];
			return PlayerEnergy.max;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Magic:
		if (PlayerStatMap.Contains(EPlayerStats::E_Magic))
		{
			FStatStruct PlayerEnergy = PlayerStatMap[EPlayerStats::E_Magic];
			return PlayerEnergy.max;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Devotion:
		if (PlayerStatMap.Contains(EPlayerStats::E_Devotion))
		{
			FStatStruct PlayerEnergy = PlayerStatMap[EPlayerStats::E_Devotion];
			return PlayerEnergy.max;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Armour:
		if (PlayerStatMap.Contains(EPlayerStats::E_Armour))
		{
			FStatStruct PlayerEnergy = PlayerStatMap[EPlayerStats::E_Armour];
			return PlayerEnergy.max;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Resistance:
		if (PlayerStatMap.Contains(EPlayerStats::E_Resistance))
		{
			FStatStruct PlayerEnergy = PlayerStatMap[EPlayerStats::E_Resistance];
			return PlayerEnergy.max;
		}
		else
			return 0.0f;
		break;
	default:
		return 0.0f;
		break;
	}

}

float UCombatComponent::GetBaseStatValue(EPlayerStats Stat)
{
	switch (Stat)
	{
	case EPlayerStats::E_HP:
		if (PlayerStatMap.Contains(EPlayerStats::E_HP))
		{
			FStatStruct PlayerEnergy = PlayerStatMap[EPlayerStats::E_HP];
			return PlayerEnergy.base;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Energy:
		if (PlayerStatMap.Contains(EPlayerStats::E_Energy))
		{
			FStatStruct PlayerEnergy = PlayerStatMap[EPlayerStats::E_Energy];
			return PlayerEnergy.base;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Speed:
		if (PlayerStatMap.Contains(EPlayerStats::E_Speed))
		{
			FStatStruct PlayerDex = PlayerStatMap[EPlayerStats::E_Speed];
			return PlayerDex.base;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Dexterity:
		if (PlayerStatMap.Contains(EPlayerStats::E_Dexterity))
		{
			FStatStruct PlayerDex = PlayerStatMap[EPlayerStats::E_Dexterity];
			return PlayerDex.base;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Might:
		if (PlayerStatMap.Contains(EPlayerStats::E_Might))
		{
			FStatStruct PlayerEnergy = PlayerStatMap[EPlayerStats::E_Might];
			return PlayerEnergy.base;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Magic:
		if (PlayerStatMap.Contains(EPlayerStats::E_Magic))
		{
			FStatStruct PlayerEnergy = PlayerStatMap[EPlayerStats::E_Magic];
			return PlayerEnergy.base;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Devotion:
		if (PlayerStatMap.Contains(EPlayerStats::E_Devotion))
		{
			FStatStruct PlayerEnergy = PlayerStatMap[EPlayerStats::E_Devotion];
			return PlayerEnergy.base;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Armour:
		if (PlayerStatMap.Contains(EPlayerStats::E_Armour))
		{
			FStatStruct PlayerEnergy = PlayerStatMap[EPlayerStats::E_Armour];
			return PlayerEnergy.base;
		}
		else
			return 0.0f;
		break;
	case EPlayerStats::E_Resistance:
		if (PlayerStatMap.Contains(EPlayerStats::E_Resistance))
		{
			FStatStruct PlayerEnergy = PlayerStatMap[EPlayerStats::E_Resistance];
			return PlayerEnergy.base;
		}
		else
			return 0.0f;
		break;
	default:
		return 0.0f;
		break;
	}


}



float UCombatComponent::GetClassRegenRate(EPlayerClass inClass)
{
	return 0.0f;
}
//float UCombatComponent::GetClassRegenRate(EPlayerClass PlayerClass)
//{
//	switch (PlayerClass)
//	{
//	case EPlayerClass::E_Caster:
//		float ManaRegen;
//
//
//
//		return ManaRegen;
//		break;
//	case EPlayerClass::E_Warrior:
//		float RageRegen;
//
//
//		return 0.0f;
//		break;
//	case EPlayerClass::E_Rogue:
//		float StaminaRegen;
//
//		
//		return StaminaRegen;
//		break;
//	default:
//		return 0.0f;
//		break;
//	}
//	
//}
#pragma endregion



// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}


