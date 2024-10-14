// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerState/MotionState/MotionStateAbstract.h"
#include "InputActionValue.h"

/**
 * 
 */
class SEEKANDSNEAK_3D_API PlayerMove : public MotionStateAbstract
{
public:
	PlayerMove();

	void Begin(ACharacter* Player, const FInputActionValue& InputValue);

private:

	/*Pre Declaring Values For Movement To Avoid Re-Declaration On Each*/

	FVector2D MovementValue;

	FVector ForwardDirection;
	FVector RightDirection;

	//For Prop Movement -- Extra Calculation For TPS Movement
	FRotator ControlRotation;
	FRotator YawRotation;
};
