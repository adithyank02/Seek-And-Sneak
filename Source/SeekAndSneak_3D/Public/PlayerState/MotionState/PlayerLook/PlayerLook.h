// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "PlayerState/MotionState/MotionStateAbstract.h"

/**
 * 
 */
class SEEKANDSNEAK_3D_API PlayerLook : public MotionStateAbstract
{
public:
	PlayerLook();
	~PlayerLook();

	void Begin(ACharacter* Player, const FInputActionValue& InputValue) override;

private:

	FVector2D MovementValue;
};
