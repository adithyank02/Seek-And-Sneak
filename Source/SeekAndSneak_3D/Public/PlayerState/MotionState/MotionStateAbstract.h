// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"

class ACharacter;

enum class MotionEnum
{
	OnMove,
	OnLook,
};

/**
 * 
 */
class SEEKANDSNEAK_3D_API MotionStateAbstract
{
public:
	MotionStateAbstract();
	virtual ~MotionStateAbstract();

	virtual void Begin(ACharacter* Player, const FInputActionValue& InputValue) = 0;
};
