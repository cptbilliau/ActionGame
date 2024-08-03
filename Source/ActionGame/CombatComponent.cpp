// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "GameFramework/Actor.h"
#include "BaseBasicAttack.h"
#include "ActionGameCharacter.h"
#include "Chaos/Deformable/Utilities.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Net/Core/PushModel/PushModel.h"

FTimerHandle BasicAttackCooldown;
FTimerHandle Slot1Cooldown;
FTimerHandle Slot2Cooldown;
FTimerHandle Slot3Cooldown;
FTimerHandle MovementCooldown;

struct FStatStruct;
class UDamageType;

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	
	// Set	 this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
   PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	
	// ...
	
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(UCombatComponent, MapCurrentStatWorkaroundArray, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(UCombatComponent, StatMapWorkaroundArray, SharedParams);
	DOREPLIFETIME(UCombatComponent, Team);
	DOREPLIFETIME(UCombatComponent, BasicAttack);
	DOREPLIFETIME(UCombatComponent, MovementSkill);
	DOREPLIFETIME(UCombatComponent, SkillSlot1);
	DOREPLIFETIME(UCombatComponent, SkillSlot2);
	DOREPLIFETIME(UCombatComponent, SkillSlot3);
}

void UCombatComponent::OnRep_CurrentStatMapWorkaround()
{
	CurrentPlayerStatMap.Reset();
	for (const FReplicatedCurrentStat_Stat_Float& ReplicateMapEntry : MapCurrentStatWorkaroundArray)
	{
		CurrentPlayerStatMap.Emplace(ReplicateMapEntry.Stat, ReplicateMapEntry.currentStat);
	}
}

void UCombatComponent::OnRep_StatMapWorkAround()
{
	PlayerStatMap.Reset();
	for (const FReplicatedBaseStat_Stat_Float& ReplicateMapEntry : StatMapWorkaroundArray)
	{
		PlayerStatMap.Emplace(ReplicateMapEntry.Stat, ReplicateMapEntry.BaseStat);
	}
}

void UCombatComponent::ReplicateCurrentStatMapWorkAround()
{
	MapCurrentStatWorkaroundArray.Reset();
	const TArray<TPair<EPlayerStats, float>>& PairArray = CurrentPlayerStatMap.Array();
	for (const TPair<EPlayerStats, float>& Pair : PairArray)
	{
		FReplicatedCurrentStat_Stat_Float RepEntry;
		RepEntry.Stat = Pair.Key;
		RepEntry.currentStat = Pair.Value;
		MapCurrentStatWorkaroundArray.Add(MoveTemp(RepEntry));
	}
	MARK_PROPERTY_DIRTY_FROM_NAME(UCombatComponent, MapCurrentStatWorkaroundArray, this);
}

void UCombatComponent::ReplicatePlayerStatMapWorkAround()
{

	StatMapWorkaroundArray.Reset();
	const TArray<TPair<EPlayerStats, FStatStruct>>& PairArray = PlayerStatMap.Array();
	for (const TPair<EPlayerStats, FStatStruct>& Pair : PairArray)
	{
		FReplicatedBaseStat_Stat_Float RepEntry;
		RepEntry.Stat = Pair.Key;
		RepEntry.BaseStat = Pair.Value;
		StatMapWorkaroundArray.Add(MoveTemp(RepEntry));
	}
	MARK_PROPERTY_DIRTY_FROM_NAME(UCombatComponent, StatMapWorkaroundArray, this);
	
}


void UCombatComponent::HandleAbilityUsage_Implementation(FTransform SpawnTransform, EAbilitySlot AttachedSlot, AActor* Owner, APawn* Instigator,
const TArray<FReplicatedCurrentStat_Stat_Float>& CurrentPlayerStats, int SkillLevel)
{
	FActorSpawnParameters spawnParameters;
	spawnParameters.Owner = GetOwner();
	TSubclassOf<ABaseAbility> AbilityToSpawn = GetAbilityBySlot(AttachedSlot);
	ABaseAbility* SpawnedAbility = GetWorld()->SpawnActorDeferred<ABaseAbility>(AbilityToSpawn, SpawnTransform, Owner, Instigator, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	if(SpawnedAbility)
	{
		SpawnedAbility->AttachedSlot = AttachedSlot;
		SpawnedAbility->OwningPlayerStatMap = CurrentPlayerStats;
		SpawnedAbility->SkillLevel = SkillLevel;
		
		UGameplayStatics::FinishSpawningActor(SpawnedAbility, SpawnTransform);
	}
	
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
		GetWorld()->GetTimerManager().SetTimer(MovementCooldown, Delagate, inCooldown, true);
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

		TimeLeft = GetWorld()->GetTimerManager().GetTimerRemaining(MovementCooldown);
		CooldownTimeRemaining.Broadcast(slot, TimeLeft);
		//SetMovementSlotCooldown
		break;
	}
	
}

TSubclassOf<ABaseAbility> UCombatComponent::GetAbilityBySlot(EAbilitySlot slot) const
{
	switch (slot)
	{
	case EAbilitySlot::E_NONE:
		//throw error do nothing
		return nullptr;
		
	case EAbilitySlot::E_BasicAttack:
		if (BasicAttack != nullptr)
		return  BasicAttack.LoadSynchronous();
		
		return nullptr;
		
		
	case EAbilitySlot::E_Slot1:
		//SetSlot1Cooldowntimer
			if (SkillSlot1 != nullptr)
		return SkillSlot1.LoadSynchronous();
			
		return nullptr;
		
	
	case EAbilitySlot::E_Slot2:
		if(SkillSlot2 != nullptr)
		return SkillSlot2.LoadSynchronous();
		
			return nullptr;
		
		break;
	case EAbilitySlot::E_Slot3:
		if(SkillSlot3 != nullptr)
		return SkillSlot3.LoadSynchronous();
		
		return nullptr;

	case EAbilitySlot::E_MovementSlot:
		if(MovementSkill != nullptr)
		return MovementSkill.LoadSynchronous();
	
		return nullptr;
	}
	return nullptr;
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
		OutImage = MovementSkill->GetDefaultObject<ABaseSkill>()->SkillImage;
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
		GetWorld()->GetTimerManager().ClearTimer(MovementCooldown);
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

	ReplicatePlayerStatMapWorkAround();

}
void UCombatComponent::ModifyBaseStatValue(EPlayerStats inStat, float ModifyBy)
{
	FStatStruct* Stat = PlayerStatMap.Find(inStat);
	
	float value = Stat->base + ModifyBy;

	float ClampedValue = FMath::Clamp(value, 0.0f, GetMaxStatValue(inStat));
	
	SetBaseStatValue(inStat, ClampedValue);
		
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
	
	ReplicateCurrentStatMapWorkAround();
}

#pragma endregion
/*

GET STAT
*/
#pragma region Get Stat
float UCombatComponent::GetCurrentStatValue(EPlayerStats Stat)
{
	return CurrentPlayerStatMap[Stat];
}
float UCombatComponent::GetMaxStatValue(EPlayerStats Stat)
{
	FStatStruct* StatToFind = PlayerStatMap.Find(Stat);

	return StatToFind->max;
}

float UCombatComponent::GetBaseStatValue(EPlayerStats Stat)
{
	FStatStruct* StatToFind = PlayerStatMap.Find(Stat);

	return StatToFind->base;
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


