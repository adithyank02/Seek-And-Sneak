// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ACharacter;

enum class InputStateEnum
{
	OnPropMorph,
	OnPropClone,
	OnHunterFire,
};

/**
 * 
 */
class SEEKANDSNEAK_3D_API InputStateAbstract
{
public:
	InputStateAbstract();
	virtual ~InputStateAbstract();

	virtual void Begin(ACharacter* Player) = 0;
	virtual void End(ACharacter* Player) = 0;

	//Non Abstract Function For Extra Functionality For Specific Class
	virtual void SetLocation(FVector V1, FVector V2);
};
