// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/MotionState/PlayerLook/PlayerLook.h"
#include "GameFramework/Character.h"

PlayerLook::PlayerLook()
{
}

PlayerLook::~PlayerLook()
{
}

void PlayerLook::Begin(ACharacter* Player, const FInputActionValue& InputValue)
{
	MovementValue = InputValue.Get<FVector2D>();

	Player->AddControllerPitchInput(MovementValue.Y);
	Player->AddControllerYawInput(MovementValue.X);

}
