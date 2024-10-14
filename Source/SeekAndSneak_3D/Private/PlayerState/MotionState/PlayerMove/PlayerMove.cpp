// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/MotionState/PlayerMove/PlayerMove.h"
#include "GameFramework/Character.h"

#include "PropPlayer/PropPlayer.h"

PlayerMove::PlayerMove()
{

}
void PlayerMove::Begin(ACharacter* Player, const FInputActionValue& InputValue)
{
	MovementValue = InputValue.Get<FVector2D>();

	if (Player->IsA(APropPlayer::StaticClass()))
	{
		ControlRotation = Player->GetController()->GetControlRotation();
		YawRotation =  FRotator(0,ControlRotation.Yaw,0);

		ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	}
	else
	{
		ForwardDirection = Player->GetActorForwardVector();
		RightDirection = Player->GetActorRightVector();
	}
	Player->AddMovementInput(ForwardDirection, MovementValue.X);
	Player->AddMovementInput(RightDirection, MovementValue.Y);
}
