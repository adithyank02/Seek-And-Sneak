// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Others/Create Widget/CreateWidgetAbstract.h"

class UWinnerShowingWidget;

/**
 * 
 */
class SEEKANDSNEAK_3D_API CreateMatchEndWidget : public CreateWidgetAbstract
{
public:
	CreateMatchEndWidget();
	~CreateMatchEndWidget();

	void Begin(APlayerController* PlayerController, ECharacterType CharacterType)override;
	void End()override;
	void ChangeWidgetSwitcherIndex(int Index)override;

private:

	UWinnerShowingWidget* WinnerWidget;

	TSubclassOf<UWinnerShowingWidget>WinnerShowingWidgetClass;
};
