// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/CommonPlayerController.h"

#include "HunterPlayer/HunterPlayer.h"
#include "PropPlayer/PropPlayer.h"

#include "PlayerController/HunterPlayerController.h"
#include "PlayerController/PropPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Runtime/Engine/Public/TimerManager.h"

#include "Kismet/KismetSystemLibrary.h"


ACommonPlayerController::ACommonPlayerController()
{

}

void ACommonPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%d"), index), true, true, FLinearColor::White, 15);
	index++;
}


void ACommonPlayerController::SetClientInputBinding_Implementation(ECharacterType CharacterType)
{
	if (IsLocalController())
	{
		if (CharacterType == ECharacterType::HunterCharacter)
		{
			GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ACommonPlayerController::BindHunterPlayerInputs);
			RemovePropInputRef();
		}
		else if (CharacterType == ECharacterType::PropCharacter)
		{
			GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ACommonPlayerController::BindPropPlayerInputs);
			RemoveHunterInputRef();
		}
		OwnerCharacterType = CharacterType;
	}

}
void ACommonPlayerController::RemoveUnwantedRef()
{
	switch (OwnerCharacterType)
	{
	case ECharacterType::HunterCharacter: RemovePropInputRef();
		break;
	case ECharacterType::PropCharacter: RemoveHunterInputRef();
	}
}

//Deleting Ref Of Input That Don't Use
void ACommonPlayerController::RemoveHunterInputRef()
{
	HunterPlayerMappingContext = nullptr;
	HunterJogAction = nullptr;
	HunterLookAction = nullptr;
	HunterSprintAction = nullptr;
	HunterFireWeaponAction = nullptr;

	delete HunterPlayerMappingContext;
	delete HunterJogAction;
	delete HunterLookAction;
	delete HunterSprintAction;
	delete HunterFireWeaponAction;
}

void ACommonPlayerController::RemovePropInputRef()
{
	PropPlayerMappingContext = nullptr;
	PropMoveAction = nullptr;
	PropLookAction = nullptr;
	PropJumpAction = nullptr;
	PropMorphAction = nullptr;
	PropCloneAction = nullptr;
	PropSmokeBombAction = nullptr;

	delete PropPlayerMappingContext;
	delete PropMoveAction;
	delete PropLookAction;
	delete PropJumpAction;
	delete PropMorphAction;
	delete PropCloneAction;
	delete PropSmokeBombAction;
}


/*--------------------------------------------------- Binding Input And Function ------------------------------------------------------------------*/

void ACommonPlayerController::BindHunterPlayerInputs()  //Hunter Input Bindings
{
	//Only Applied By The LocalPlayer
	if (IsLocalController())
	{
		SetInputMode(FInputModeGameOnly());

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			//Setting Up The Mapping Context
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(HunterPlayerMappingContext, 0);
		}

		if (UEnhancedInputComponent* EnhancedInput = Cast <UEnhancedInputComponent>(this->InputComponent))
		{
			if (AHunterPlayer* HunterPlayer = Cast<AHunterPlayer>(GetPawn()))
			{
				//Binding InputAction And The Correspoding Functions
				EnhancedInput->BindAction(HunterJogAction, ETriggerEvent::Triggered, HunterPlayer, &AHunterPlayer::PlayerJogFunction);
				EnhancedInput->BindAction(HunterLookAction, ETriggerEvent::Triggered, HunterPlayer, &AHunterPlayer::LookFunction);

				EnhancedInput->BindAction(HunterSprintAction, ETriggerEvent::Triggered, HunterPlayer, &AHunterPlayer::StartSprintFunction);
				EnhancedInput->BindAction(HunterSprintAction, ETriggerEvent::Completed, HunterPlayer, &AHunterPlayer::StopSprintFunction);

				EnhancedInput->BindAction(HunterFireWeaponAction, ETriggerEvent::Started, HunterPlayer, &AHunterPlayer::StartFiringWeapon);
				EnhancedInput->BindAction(HunterFireWeaponAction, ETriggerEvent::Completed, HunterPlayer, &AHunterPlayer::StopFiringWeapon);

				UKismetSystemLibrary::PrintString(GetWorld(), GetPawn()->GetName(),true,true,FLinearColor::Black,10);

			}
		}
	}
}

void ACommonPlayerController::BindPropPlayerInputs()   //Prop Input Bindings
{
	if (IsLocalController())
	{
		SetInputMode(FInputModeGameOnly());

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			//Setting Up The Mapping Context
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(PropPlayerMappingContext, 0);
		}

		if (UEnhancedInputComponent* EnhancedInput = Cast <UEnhancedInputComponent>(this->InputComponent))
		{
			if (APropPlayer* PropPlayer = Cast<APropPlayer>(GetPawn()))
			{
				//Binding InputAction And The Correspoding Functions
				EnhancedInput->BindAction(PropMoveAction, ETriggerEvent::Triggered, PropPlayer, &APropPlayer::MoveFunction);
				EnhancedInput->BindAction(PropLookAction, ETriggerEvent::Triggered, PropPlayer, &APropPlayer::LookFunction);

				EnhancedInput->BindAction(PropJumpAction, ETriggerEvent::Started, PropPlayer, &APropPlayer::StartJumpFunction);
				EnhancedInput->BindAction(PropJumpAction, ETriggerEvent::Started, PropPlayer, &APropPlayer::StopJumpFunction);

				EnhancedInput->BindAction(PropMorphAction, ETriggerEvent::Started, PropPlayer, &APropPlayer::MorphObjectFunction);

				EnhancedInput->BindAction(PropCloneAction, ETriggerEvent::Started, PropPlayer, &APropPlayer::PropCloneFunction);

				EnhancedInput->BindAction(PropSmokeBombAction, ETriggerEvent::Started, PropPlayer, &APropPlayer::SmokeBombFunction);

				
			}
		}

	}
}

