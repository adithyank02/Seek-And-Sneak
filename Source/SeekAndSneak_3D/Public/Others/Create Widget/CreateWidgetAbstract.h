// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Others/EnumClass/CharacterTypeEnum.h"


enum class EWidgetType : uint8
{
	PreMatchWidget,
	InMatchWidget,
	PostMatchWidget,
};

/**
 * 
 */
class SEEKANDSNEAK_3D_API CreateWidgetAbstract
{
public:
	CreateWidgetAbstract();
	virtual ~CreateWidgetAbstract();

	virtual void Begin(APlayerController* PlayerController, ECharacterType CharacterType) = 0;
};
