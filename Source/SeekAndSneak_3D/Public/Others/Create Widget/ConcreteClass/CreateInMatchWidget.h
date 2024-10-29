// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Others/Create Widget/CreateWidgetAbstract.h"

class UHunterInMatchWidget;
class UPropInMatchWidget;

/**
 * 
 */
class SEEKANDSNEAK_3D_API CreateInMatchWidget : public CreateWidgetAbstract
{
public:
	CreateInMatchWidget();
	~CreateInMatchWidget();

	void Begin(APlayerController* PlayerController, ECharacterType CharacterType)override;
	void End()override;
	void ChangeWidgetSwitcherIndex(int Index)override;

private:

	ECharacterType PlayerCharacterType;

	UHunterInMatchWidget* HunterWidget;
	TSubclassOf<UHunterInMatchWidget>HunterInMatchWidgetClass;

	UPropInMatchWidget* PropWidget;
	TSubclassOf<UPropInMatchWidget>PropInMatchWidgetClass;

	void RemovePointerRef();
	
};
