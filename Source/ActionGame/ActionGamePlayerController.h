// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInterface.h"
#include "CommonUI/Public/CommonActivatableWidget.h"
#include "CommonUI/Public/CommonActionWidget.h"

#include "Engine/DecalActor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/DecalComponent.h"




#include "ActionGamePlayerController.generated.h"

class UDecalActor;
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */


UCLASS()
class ACTIONGAME_API AActionGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public: 
	AActionGamePlayerController();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector CachedLookDestination;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FHitResult CachedHitResult;
	
protected:

	virtual void SetupInputComponent() override;

	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override; 
	
	
};
