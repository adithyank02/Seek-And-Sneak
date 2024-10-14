// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/PropPlayerController.h"
#include "PropPlayer/PropPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void APropPlayerController::BeginPlay()
{
	//Only Applied By The LocalPlayer
	if (GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			//Setting Up The Mapping Context
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}


		if (UEnhancedInputComponent* EnhancedInput = Cast <UEnhancedInputComponent>(this->InputComponent))
		{
			if (APropPlayer* PropPlayer = Cast<APropPlayer>(GetPawn()))
			{
				//Binding InputAction And The Correspoding Functions
				EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, PropPlayer, &APropPlayer::MoveFunction);
				EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, PropPlayer, &APropPlayer::LookFunction);

				EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, PropPlayer, &APropPlayer::StartJumpFunction);
				EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, PropPlayer, &APropPlayer::StopJumpFunction);

				EnhancedInput->BindAction(MorphAction, ETriggerEvent::Started, PropPlayer, &APropPlayer::MorphObjectFunction);

				EnhancedInput->BindAction(CloneAction, ETriggerEvent::Started, PropPlayer, &APropPlayer::PropCloneFunction);

				EnhancedInput->BindAction(SmokeBombAction, ETriggerEvent::Started, PropPlayer, &APropPlayer::SmokeBombFunction);

			}
		}
	}
}
