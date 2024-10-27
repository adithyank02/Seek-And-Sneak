// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Others/Create Widget/CreateWidgetAbstract.h"


/**
 * 
 */
class SEEKANDSNEAK_3D_API CreatePreMatchWidget : public CreateWidgetAbstract
{
public:
	CreatePreMatchWidget();
	~CreatePreMatchWidget();

private:

	void Begin(APlayerController* PlayerController, ECharacterType CharacterType)override;

protected:

	TSubclassOf<class UCharacterPreMatchWidget>PreMatchWidgetClass;
};
