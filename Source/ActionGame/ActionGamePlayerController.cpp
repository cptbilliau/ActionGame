// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGamePlayerController.h"


#include "GameFramework/Pawn.h"

#include "ActionGameCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AActionGamePlayerController::AActionGamePlayerController()
{
	bShowMouseCursor = true;
	
	//TargeterDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Targeter Decal"));
	
	//TargeterDecal->SetMaterial(0, TargeterMat);
}



void AActionGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
	
}





void AActionGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		//EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AActionGamePlayerController::LookAtMouse);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

}
void AActionGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;
	
	FCollisionQueryParams LineTraceParams;
	const FName LineTrace("Line");
	LineTraceParams.TraceTag = LineTrace;
	bool bHitSuccesful = false;
	
	
	
	
	bHitSuccesful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
		
	if (bHitSuccesful)
	{
		CachedLookDestination = Hit.Location;
		CachedHitResult = Hit;
		//TargeterDecal->GetDefaultObject<ADecalActor>()->SetActorLocation(CachedLookDestination);
		
		//UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, Hit.Location, FColor(100, 0, 0));
		
		
	}
	
	
	APawn* ControlledPawn = GetPawn();

	if (ControlledPawn != nullptr)
	{
		
		FVector PlayerLoc = ControlledPawn->GetActorLocation();
		ControlledPawn->FaceRotation(UKismetMathLibrary::FindLookAtRotation(PlayerLoc, CachedLookDestination));
		//ControlledPawn->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(PlayerLoc, CachedLookDestination));
	}

}




